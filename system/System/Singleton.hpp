/*
 * Singleton.hpp
 *
 * singleton template for general usage.
 *
 */
#ifndef INCLUDE_SYSTEM_SINGLETON_HPP_FILE
#define INCLUDE_SYSTEM_SINGLETON_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/checked_delete.hpp>
#include <cassert>

#include "System/AtExit.hpp"
#include "System/Threads/SafeInitLocking.hpp"

namespace System
{
namespace detail
{
Threads::SafeInitLock::MutexType &getSingletonMutex(void);
} // namespace detail

/** \brief Mayer's singleton implementation on template.
 *
 * implementation is enhanced to allow secure usage, allowing
 * creating objects in proper order destroying in reverse order.
 *
 * notice that if ogerd of creation/destruction must be preserved
 * singleton A using singleton B must call B::get() in its c-tor
 * to ensure they are created in proper order.
 *
 * singleton can be safely used before main(), in global constructors
 * and from multiple threads. it should NOT be used in destructors
 * of global objects though, since it may lead to dongling pointer
 * dereference, under certain conditions.
 *
 * \note it is recommended to make constructor of class T
 *       private and make Singleton<T> its friend. this ensures
 *       that instances of T won't be made directly by user.
 *       T should not noncopyable as well.
 *
 */
template<typename T>
class Singleton: private boost::noncopyable
{
public:
  /** \brief get pointer to singleton internal type
   *
   *  singleton object is created on heap for increased
   *  generality (in case T would be huge object).
   *
   *  \return object instance pointer. pointer is returned
   *          instead of reference since it is harder to
   *          accidently make obj-copy this way.
   */
  inline static T *get(void)
  {
    // TODO: using this in a running thread, after leaving
    //       main() may cause dongling-pointer dereference.
    //       it should be fixed (shared_ptr+weak_ptr?).
    static T *t=NULL;
    if(t==NULL)
    {
      // all singletons locked with the same mutex - overkill, but secure.
      Threads::SafeInitLock lock( detail::getSingletonMutex() );
      if(t==NULL)
        init(&t);
    }
    assert(t!=NULL && "object's initialization failed");
    return t;
  }

private:
  // special deallocator type that ensures to NULL internal
  // pointer as well.
  class SingletonDeallocator: public AtExitResourceDeallocator
  {
  public:
    // create member when initialized
    explicit SingletonDeallocator(T **dstPtr):
      dstPtr_(dstPtr)
    {
      assert(dstPtr!=NULL);     // check input
      *dstPtr_=new T;           // create pointer
      assert(*dstPtr!=NULL);    // just in case... (RAII assumed)
    }
    // free when exiting
    virtual ~SingletonDeallocator(void)
    {
      assert(*dstPtr_==NULL);           // object should be already freed
      deallocate();                     // just in case...
    }
    // deallocation on exit
    virtual void deallocate(void)
    {
      boost::checked_delete(*dstPtr_);  // delete object
      *dstPtr_=NULL;                    // mark pointer as unusable
    }
  private:
    T **dstPtr_;
  }; // class SingletonDeallocator

  // helper method that creates output object. this allows to keep
  // singleton's get() as clean and simple as possible.
  static void init(T **dstPtr)
  {
    assert(dstPtr!=NULL);
    // register singleton's deallocator
    AtExit::TDeallocPtr dealloc( new SingletonDeallocator(dstPtr) );
    assert( dealloc.get()!=NULL );
    AtExit::registerDeallocator(dealloc);
    assert(*dstPtr!=NULL);
  } // init()

  Singleton(void);  // no instances allowed
}; // class Singleton

} // namespace System

#endif


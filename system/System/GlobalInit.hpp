/*
 * GlobalInit.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_GLOBALINIT_HPP_FILE
#define INCLUDE_SYSTEM_GLOBALINIT_HPP_FILE

/* public header */

#include "System/Threads/SafeInitLocking.hpp"
#include "System/AtExit.hpp"

namespace System
{

namespace detail
{
/** \brief helper function giving access to global mutex.
 *  \return reference to global mutex used for locking GlobalInit() internals.
 */
Threads::SafeInitLock::MutexType &getGlabalInitMutex(void);
} // namespace detail

/**
 * \brief template wrapper for global (de)initilization oof data.
 *
 * number of libraries uses global data that are not initialized
 * in the proper way, sometimes are not uninitializaed at all, initalizaiton
 * is not thread safe, etc... this wrapper solves this issues.
 *
 * this class initializes user object in thread-safe way, and uninitializes
 * it uppon program exit. when it is needed once more, it will be
 * re-initialized and deallocated stright away.
 *
 * used-defined T type has to provide static methods init() and uninit()
 * that performs as-is initialization (i.e. no locking, checks, etc... are
 * required - it is all done by GlobalInit<> template) and uninitialization
 * of given element, respecitively.
 * when init() throws, uninit() is never called.  uninit() must NOT throw!
 *
 * init() is ensured to be called exactly once, during the first object's
 * creation (thread safe, with valid object creation order preserved).
 * uninit() is ensured to be called exactly once (if init() didn't throw)
 * when program exits. it is ensured that uninit() will NOT be called
 * until main() exits and last object holds GlobalInit<> copy. notice however
 * that when new GlobalInit<> instances will be created after leaving main()
 * it may happen that init()+uninit() sequence will be called more than once,
 * in proper order.
 *
 * typical usage in code goes as follows:
 * <code>
 *   namespace detail
 *   {
 *     struct MyLibInitImpl
 *     {
 *       static void init(void)
 *       {
 *         // initialization code for MyLib here
 *       }
 *       static void uninit(void)
 *       {
 *         // uninitialization code for MyLib here
 *       }
 *     };
 *   }
 *   typedef System::GlobalInit<detail::MyLibInitImpl> MyLibInit;
 *   // ...
 *   MyLibInit mylibinit;
 *   // from this point in time MyLib is initialized and can be used.
 *   // ...
 * </code>
 *
 * notice that it is good practice to keep GlobalInit<> instance as a private
 * object member for those elements that relay on given library to be initialized.
 */
template<typename T>
class GlobalInit
{
public:
  /** \brief create handle object.
   *
   *  initializes library, if not already initialized. increases usage count.
   */
  GlobalInit(void)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    if( counter(lock)==0 )
    {
      GlobalUninit        *tmp=new GlobalUninit();
      AtExit::TDeallocPtr  uninit(tmp);     // put to auto-ptr
      AtExit::registerDeallocator(uninit);
      T::init();                            // initialize user object
      tmp->unlock(lock);                    // allow deallocation in atexit()
      atExitMark(lock)=false;
    }
    // mark usage
    ++counter(lock);
  }

  /** \brief copy constructor.
   *
   *  increases reference count.
   */
  GlobalInit(const GlobalInit &/*other*/)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    assert( counter(lock)>0 );
    // mark usage
    ++counter(lock);
  }

  /** \brief assignment operator.
   *  \return const-reference to this object.
   */
  const GlobalInit &operator=(const GlobalInit &/*other*/)
  {
    // NOTE: nothing has to be done here, since each copy is equivalent to
    //       other (no private fields) and overwriting one instance with
    //       another does not change total objects count (i.e. object being
    //       assigned to already exists).
    return *this;
  }

  /** \brief destroy object being referenced.
   *
   *  decreases reference count. if this is last instance holding reference
   *  and atexit() is already done, this will uninitialize library as well.
   */
  ~GlobalInit(void)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    assert( counter(lock)>0 );
    // mark usage
    --counter(lock);
    // if this is the last instance and atexit() has been already
    // finished we have to deallocate ourselves
    if( counter(lock)==0 && atExitMark(lock)==true )
    {
      T::uninit();
      atExitMark(lock)=false;
    }
  }

private:
  // helper class to uninitialize given library
  class GlobalUninit: public AtExitResourceDeallocator
  {
  public:
    GlobalUninit(void):
      unlocked_(false)
    {
    }
    // enable deallocation feature
    void unlock(Threads::SafeInitLock &)
    {
      unlocked_=true;
    }
    // deallocation itself
    virtual void deallocate(void)
    {
      Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
      if(unlocked_==false)      // something failed during initialization - do nothing
        return;
      if( counter(lock)==0 )    // only if noone is using this any more
        T::uninit();
      atExitMark(lock)=true;    // mark that atexit() has been already done
    }

  private:
    bool unlocked_;
  }; // class GlobalUninit

  // this must be done within a lock to ensure safe initialization
  static unsigned long &counter(Threads::SafeInitLock &)
  {
    static unsigned long cnt=0;
    return cnt;
  }
  // mark that atexit handle has already finished
  static bool &atExitMark(Threads::SafeInitLock &)
  {
    static bool mark=false;
    return mark;
  }
}; // class GlobalInit

} // namespace System

#endif

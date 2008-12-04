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
#include <cassert>

#include "System/AtExit.hpp"


namespace System
{

/** \brief Mayer's singleton implementation on template.
 *
 * implementation is enhanced to allow secure usage, allowing
 * creating objects in proper order destroying in reverse order.
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
    static T *t=init();
    assert(t!=NULL);
    return t;
  }

private:
  static T *init(void)
  {
    std::auto_ptr<T> ap(new T);
    assert( ap.get()!=NULL );
    T *t=ap.get();
    // TODO
    return t;
  }

  Singleton(void);  // no instances allowed
}; // class Singleton

} // namespace System

#endif


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
#include <assert.h>


namespace System
{

template<typename T>
class Singleton: private boost::noncopyable
{
public:
  // get pointer to singleton internal type
  inline static T *get(void)
  {
    static boost::scoped_ptr<T> s( new T );
    assert( s.get()!=NULL );
    return s.get();
  }

private:
  Singleton(void);  // no instances allowed
}; // class Singleton

} // namespace System

#endif


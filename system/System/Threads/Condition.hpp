/*
 * Condition.hpp
 *
 * class wrapping around conditional variable from
 * pthreads.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_CONDITION_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_CONDITION_HPP_FILE

/* public header */

#include <pthread.h>
#include <boost/noncopyable.hpp>

#include "System/Exception.hpp"


namespace System
{
namespace Threads
{

// forward declaration
class Conditional;

//
// thin wrapper for pthread's conditional variable
//
class Condition: private boost::noncopyable
{
public:
  Condition(void)
  {
    if( pthread_cond_init(&_cond, NULL)!=0 )
      throw System::Exception("Condition::Condition(): "
                              "pthread_cond_init() failed");
  }
  ~Condition(void)
  {
    pthread_cond_destroy(&_cond);
  }

private:
  friend class System::Threads::Conditional;

  pthread_cond_t _cond;     // conditional variable
}; // class Condition

} // namespace Threads
} // namespace System

#endif


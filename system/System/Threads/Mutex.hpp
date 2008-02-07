/*
 * Mutex.hpp
 *
 * represents mutex. lock/unlock is made by
 * Lock friend class
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_MUTEX_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_MUTEX_HPP_FILE

/* public header */

#include <pthread.h>
#include <errno.h>
#include <boost/noncopyable.hpp>

#include "System/Exception.hpp"


namespace System
{
namespace Threads
{

// forward declarations
class GeneralLock;
class Conditional;

class Mutex: private boost::noncopyable
{
public:
  Mutex(void);
  ~Mutex(void);

private:
  friend class System::Threads::GeneralLock;
  friend class System::Threads::Conditional;

  // everything below can be used by GeneralLock
  void lock(void);
  bool trylock(void);
  void unlock(void);

  pthread_mutex_t _mutex;
}; // class Mutex

} // namespace Threads
} // namespace System

#endif


/*
 * GeneralLock.hpp
 *
 * critical sections basic class.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_GENERALLOCK_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_GENERALLOCK_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>

#include "System/Threads/Mutex.hpp"


namespace System
{
namespace Threads
{

//
// this code is separated as a class to allow
// single friend-class in Mutex.
//
class GeneralLock: private boost::noncopyable
{
protected:
  GeneralLock(Mutex &mutex):
    _mutex(mutex)
  {
  }

  void lock(void)
  {
    _mutex.lock();
  }
  bool trylock(void)
  {
    return _mutex.trylock();
  }
  void unlock(void)
  {
    _mutex.unlock();
  }

private:
  Mutex &_mutex;
}; // class Lock

} // namespace Threads
} // namespace System

#endif


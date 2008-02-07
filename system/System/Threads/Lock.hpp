/*
 * Lock.hpp
 *
 * critical section implementation.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_LOCK_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_LOCK_HPP_FILE

/* public header */

#include "System/Threads/GeneralLock.hpp"


namespace System
{
namespace Threads
{

class Lock: private System::Threads::GeneralLock
{
public:
  inline Lock(Mutex &mutex):
    GeneralLock(mutex)
  {
    lock();
  }
  inline ~Lock(void)
  {
    unlock();
  }
}; // class Lock

} // namespace Threads
} // namespace System

#endif


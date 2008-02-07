/*
 * TryLock.hpp
 *
 * critical section implementation. locks mutex only
 * if locking is possible.
 *
 * note: construction DOESN'T lock mutex by default!
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_TRYLOCK_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_TRYLOCK_HPP_FILE

/* public header */

#include "System/Threads/GeneralLock.hpp"


namespace System
{
namespace Threads
{

class TryLock: private System::Threads::GeneralLock
{
public:
  TryLock(System::Threads::Mutex &mutex);
  ~TryLock(void);

  // try locking mutex, and return if it succeded
  bool trylock(void);

private:
  unsigned int _cnt;    // lock count
}; // class TryLock

} // namespace Threads
} // namespace System

#endif


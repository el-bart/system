/*
 * TryLock.cpp
 *
 */

#include "System/Threads/TryLock.hpp"


namespace System
{
namespace Threads
{

TryLock::TryLock(System::Threads::Mutex &mutex):
  GeneralLock(mutex),
  _cnt(0)
  {
  }


TryLock::~TryLock(void)
{
  // release recurrent lock as many times as it was locked.
  // simple, unconditional unlock doesn't work here, since
  // trylock() might not have been called here.
  for(; _cnt!=0; --_cnt)
    unlock();
}


bool TryLock::trylock(void)
{
  if( GeneralLock::trylock() )    // locking succeded?
  {
    ++_cnt;           // mark locking
    return true;
  }
  return false;       // locking failed
}

} // namespace Threads
} // namespace System


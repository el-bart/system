/*
 * Mutex.cpp
 *
 */
#include <stdlib.h>

#include "System/Threads/Mutex.hpp"


namespace System
{
namespace Threads
{

Mutex::Mutex(void)
{
  // prepare mutex attributes
  pthread_mutexattr_t mta;
  pthread_mutexattr_init(&mta);
  int ret=pthread_mutexattr_settype(&mta, PTHREAD_MUTEX_RECURSIVE);
  // init mutex
  pthread_mutex_init(&_mutex, &mta);
  // free mutex attributes
  pthread_mutexattr_destroy(&mta);

  // throw if error occured
  if(ret!=0)
    throw System::Exception("Mutex::Mutex(): "
                            "pthread_mutexattr_settype() failed");
}


Mutex::~Mutex(void)
{
  pthread_mutex_destroy(&_mutex);
}


void Mutex::lock(void)
{
  if( pthread_mutex_lock(&_mutex)!=0 )
    throw System::Exception("Mutex::lock(): "
                            "pthread_mutex_lock() returned error");
}


bool Mutex::trylock(void)
{
  // try locking and return proper status
  switch( pthread_mutex_trylock(&_mutex) )
  {
    case 0:       // all ok and locking succeded
      return true;
    case EBUSY:   // all ok, but locking failed
      return false;
    default:      // error occurred :(
      throw System::Exception("Mutex::trylock(): "
                              "pthread_mutex_trylock() returned error");
  }
}


void Mutex::unlock(void)
{
  if( pthread_mutex_unlock(&_mutex)!=0 )
    throw System::Exception("Mutex::unlock(): "
                            "pthread_mutex_unlock() returned error");
}

} // namespace Threads
} // namespace System


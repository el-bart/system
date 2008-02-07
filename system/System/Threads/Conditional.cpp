/*
 * Conditional.cpp
 *
 */

#include "System/Threads/Lock.hpp"
#include "System/Threads/Conditional.hpp"


namespace System
{
namespace Threads
{

Conditional::Conditional(bool test):
  _test(test)
{
}


void Conditional::wait(void)
{
  // wait and check if condition is met:
  Lock lock(_mutex);    // required by conditional variable
  while( !testCondition() )
    if( pthread_cond_wait(&_cond._cond, &_mutex._mutex)!=0 )
      throw System::Exception("Conditional::wait(): "
                              "pthread_cond_wait() failed");
}


bool Conditional::wait(unsigned int uSecs)
{
  const timespec timeout={ uSecs/(1000000)+time(NULL),
                          (uSecs%1000000)*1000 };
  // wait and check if condition is met:
  Lock lock(_mutex);    // required by conditional variable
  while( !testCondition() )
  {
    switch( pthread_cond_timedwait(&_cond._cond,
                                   &_mutex._mutex,
                                   &timeout) )
    {
      case 0:           // all ok
        return true;

      case ETIMEDOUT:   // wait timeouted
        return false;

      default:          // error... :(
        throw Exception("Conditional::wait(): "
                        "pthread_cond_wait() failed");
    } // switch(wait())
  } // while(!cond)

  // never reach here
  return false;
}


void Conditional::signalOne(void)
{
  Lock lock(_mutex);
  if( pthread_cond_signal(&_cond._cond)!=0 )
    throw System::Exception("Conditional::signalOne(): "
                            "pthread_cond_signal() failed");
}


void Conditional::signalAll(void)
{
  Lock lock(_mutex);
  if( pthread_cond_broadcast(&_cond._cond)!=0 )
    throw System::Exception("Conditional::signalAll(): "
                            "pthread_cond_broadcast() failed");
}


void Conditional::setCondition(bool val)
{
  Lock lock(_mutex);
  _test=val;
}


bool Conditional::testCondition(void)
{
  Lock lock(_mutex);
  return _test;
}

} // namespace Threads
} // namespace System


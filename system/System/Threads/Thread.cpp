/*
 * Thread.cpp
 *
 */

#include "System/Threads/Lock.hpp"
#include "System/Threads/Thread.hpp"

#include <iostream>
#include <pthread.h>
#include <assert.h>

using namespace std;


namespace System
{
namespace Threads
{

Thread::Thread(ThreadData &td):
  _td(td),
  _finish(false),
  _isRunning(false)
{
}


Thread::~Thread(void)
{
  stop();
}


void Thread::start(void)
{
  Lock lock(_mutex);
  if( isRunning() )
    throw System::Exception("Thread::start(): "
                            "thread's already running");
  _finish=false;

  // set attributes for threads, since default values doesn't work
  // well on some systems...
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
  pthread_attr_setschedpolicy (&attr, SCHED_OTHER            );
  pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED  );
  pthread_attr_setscope       (&attr, PTHREAD_SCOPE_SYSTEM   );

  if( pthread_create(&_thread, &attr, Thread::run, this)!=0 )
    throw System::Exception("Thread::start(): "
                            "thread creation failed");
  _isRunning=true;
}


void Thread::stop(void)
{
  Lock lock(_mutex);
  if( !isRunning() )              // multiple 'stops' allowed
    return;
  cancelThread();
  waitForFinish();
}


void Thread::cancelThread(void)
{
  // this is done internaly and does not reuire locking
  _finish=true;
}


void *Thread::run(void *ptr)
{
  // this is done internaly and does not require locking
  try
  {
    Thread &th=*reinterpret_cast<Thread*>(ptr);
    while(!th._finish)
      th._td.doTask();
  }
  catch(const std::exception &ex)
  {
    cerr<<"Thread::run(): exception cought..."<<endl;
    cerr<<"Thread::run(): "<<ex.what()<<endl;
    assert(!"Thread::run(): "
            "doTask() may NOT throw at any circumstances");
    // in case of non-debug mode
    abort();
  }
  catch(...)
  {
    cerr<<"Thread::run(): exception cought..."<<endl;
    assert(!"Thread::run(): "
            "doTask() may NOT throw at any circumstances");
    // in case of non-debug mode
    abort();
  }
  return NULL;
}


void Thread::waitForFinish(void)
{
  // this is done internaly and does not reuire locking
  if( !isRunning() )    // just pass if already stopped
    return;

  pthread_join(_thread, NULL);
  _isRunning=false;
  _finish   =false;
}

}; // namespace Threads
}; // namespace System


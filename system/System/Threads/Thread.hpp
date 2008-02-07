/*
 * Thread.hpp
 *
 * thread object - specyfies how threads are beeing run.
 * th use it, derive from this class and implement doTask()
 * method.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_THREAD_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_THREAD_HPP_FILE

/* public header */

// this is HIGHLY recommended for the kernel code...
#define _MULTI_THREADED

#include <boost/noncopyable.hpp>

#include "System/Threads/Mutex.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Threads
{

class Thread: private boost::noncopyable
{
public:
  //
  // this class should be user-implemented, to perform
  // single step operation (doTaks() method).
  //
  class ThreadData
  {
  public:
    virtual ~ThreadData(void)
    {
    }
  private:
    friend class System::Threads::Thread;
    virtual void doTask(void)=0;
  }; // class ThreadData

  // td - data and processing element - user provided.
  //      it is not copyied, so parrent must be alive.
  Thread(ThreadData &td);
  ~Thread(void);

  // start thread (staring of already started is error)
  void start(void);
  // stop thread (multiple stopping is allowed). this call
  // will block until thread is not joined.
  void stop(void);

  // check if current thread is running
  bool isRunning(void) const
  {
    // this is simple value, and its read isn't critical,
    // so it can be read without locking (optimisation).
    return _isRunning;
  };

private:
  void cancelThread(void);
  void waitForFinish(void);
  static void *run(void *ptr);

  pthread_t      _thread;           // thread 'reference'
  ThreadData    &_td;               // doTask() + its data
  volatile bool  _finish;           // should we finish?
  volatile bool  _isRunning;        // is thread running?
  Mutex          _mutex;            // mutex used for methods of this class
};

}; // namespace Threads
}; // namespace System

#endif


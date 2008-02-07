/*
 * Conditional.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/Conditional.hpp"
#include "System/Threads/Thread.hpp"

namespace
{
class TestThreadData: public System::Threads::Thread::ThreadData
{
public:
  TestThreadData(System::Threads::Conditional &c):
    _counter(0),
    _timeout(0),
    _c(c)
  {
  }

  unsigned int _counter;
  unsigned int _timeout;

private:
  System::Threads::Conditional &_c;

  virtual void doTask(void)
  {
    try
    {
      if(_timeout==0)
        _c.wait();
      else
        if( !_c.wait(_timeout) )
          throw System::Exception("TestThreadData::doTask(): "
                                  "wait() timeouted");

      ++_counter;
      _c.setCondition(false);   // stop after one step
    }
    catch(const System::Exception &ex)
    {
      tut::fail( ex.what() );
    }
  }
}; // struct TestThreadData


// exception that is NOT declared anywhere else
struct SomeTestException
{
};

} // unnamed namespace


namespace System
{
namespace Threads
{

struct ConditionalTestClass
{
  ConditionalTestClass():
    _ttd(_c),
    _th(_ttd)
  {
  }
  ~ConditionalTestClass(void)
  {
    // this will prevent locks when throwing during
    // wait() on unmet condition
    _c.setCondition(true);
    _c.signalAll();
  }

  Conditional    _c;
  TestThreadData _ttd;
  Thread         _th;
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::ConditionalTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/Conditional");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// test if wait() passes on met condition
template<>
template<>
void testObj::test<1>(void)
{
  Conditional c(true);
  c.wait();
}

// test if wait()+signalOne() works
template<>
template<>
void testObj::test<2>(void)
{
  _th.start();

  // thread should stop now
  usleep(100*1000);
  ensure(_ttd._counter==0);

  // move thread single step ahead
  _c.setCondition(true);
  _c.signalOne();
  usleep(100*1000);
  ensure(_ttd._counter==1);

  // move thread single step ahead
  _c.setCondition(true);
  _c.signalOne();
  usleep(100*1000);
  ensure(_ttd._counter==2);
}

// test if wait()+signalAll() works
template<>
template<>
void testObj::test<3>(void)
{
  _th.start();

  // thread should stop now
  usleep(100*1000);
  ensure(_ttd._counter==0);

  // move thread single step ahead
  _c.setCondition(true);
  _c.signalAll();
  usleep(100*1000);
  ensure(_ttd._counter==1);
}

// test if throwing when blocked on condition will work
template<>
template<>
void testObj::test<4>(void)
{
  try
  {
    _th.start();
    usleep(100*1000);

    throw SomeTestException();
  }
  catch(const SomeTestException &ex)
  {
    // this is expected and we should reach here
  }
}

// test timeout for wait()
template<>
template<>
void testObj::test<5>(void)
{
  if( _c.wait(100*1000) )  // timeout 0.1[s]
    fail("wait() didn't return false upon timeout");
}

// test if wait() with timeout can pass
template<>
template<>
void testObj::test<6>(void)
{
  _th.start();                 // start thread
  _ttd._timeout=2*1000*1000;   // 2[s]
  usleep(100*1000);            // wait to ensure thread will block
  ensure( _th.isRunning() );
  _c.setCondition(true);
  _c.signalAll();              // reset to use timeout
  usleep(100*1000);            // wait to ensure thread will block again
  ensure("counter is not incremented (1)", _ttd._counter==1);

  // now will block with timeout
  ensure( _th.isRunning() );
  _c.setCondition(true);
  _c.signalAll();              // reset to use timeout
  usleep(100*1000);            // wait to ensure thread will block again
  ensure("counter is not incremented (2)", _ttd._counter==2);
}

} // namespace tut


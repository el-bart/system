/*
 * Thread.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/Thread.hpp"


namespace
{

class TestThreadData: public System::Threads::Thread::ThreadData
{
public:
  TestThreadData(unsigned int cnt=0):
    _cnt(cnt)
  {
  }

  unsigned int getCnt(void) const
  {
    return _cnt;
  }
private:
  virtual void doTask(void)
  {
    ++_cnt;
    usleep(10*1000);    // sleep 10[ms]
  }

  unsigned int _cnt;
}; // TestThreadData

} // unnamed namespace

namespace System
{
namespace Threads
{

struct ThreadTestClass
{
  ThreadTestClass(void):
    _th(_td)
  {
  }

  TestThreadData _td;
  Thread         _th;
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::ThreadTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/Thread");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// test for resources leak
template<>
template<>
void testObj::test<1>(void)
{
  for(int i=0; i<260; ++i)
  {
    Thread th(_td);
    th.start();
    th.stop();
  }
}

// check if thread is running
template<>
template<>
void testObj::test<2>(void)
{
  _th.start();
  ensure( _th.isRunning() );
  usleep(100*1000);         // sleep 100[ms] to make shure thread
                            // run at least one loop
  ensure( _th.isRunning() );
  _th.stop();
  ensure( !_th.isRunning() );

  // check if data has truely processed
  ensure( _td.getCnt()>0 );
}

// multiple start should throw
template<>
template<>
void testObj::test<3>(void)
{
  _th.start();  // this is ok
  try
  {
    _th.start();    // this should throw
    fail("multiple starting didn't throw as expaected");
  }
  catch(const Exception &ex)
  {
    // this is expected
  }
}

// check if stop works
template<>
template<>
void testObj::test<4>(void)
{
  _th.start();
  usleep(10*1000);  // wait some time
  _th.stop();
  unsigned int cnt=_td.getCnt();
  usleep(10*1000);  // wait some time
  ensure( cnt==_td.getCnt() );
}

// check if multiple stops works fine
template<>
template<>
void testObj::test<5>(void)
{
  ensure( !_th.isRunning() );
  _th.stop();
  ensure( !_th.isRunning() );

  _th.start();
  ensure( _th.isRunning() );

  _th.stop();
  ensure( !_th.isRunning() );

  _th.stop();
  ensure( !_th.isRunning() );

  _th.stop();
  ensure( !_th.isRunning() );
}

} // namespace tut


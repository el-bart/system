/*
 * ExternalLock.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/ExternalLock.hpp"
#include "System/Threads/TryLock.hpp"
#include "System/Threads/Thread.hpp"


namespace System
{
namespace Threads
{

struct ExternalLockTestClass
{
  struct TestThreadData: public Thread::ThreadData
  {
    TestThreadData(Mutex &m, ExternalLockTestClass *ptr):
      _m(m),
      _go(false),
      _end(false),
      _ptr(ptr)
    {
    }

    Mutex         &_m;
    volatile bool  _go;
    volatile bool  _end;
    ExternalLockTestClass *_ptr;
  private:
    virtual void doTask(void)
    {
      while(!_go);
      ExternalLock<ExternalLockTestClass> el(*_ptr);
      while(!_end);
    }
  };

  ExternalLockTestClass(void):
    _td( TestThreadData(_mutex, this) ),
    _t(_td)
  {
  }

  ~ExternalLockTestClass(void)
  {
    // this should stop thread regardless of its state
    _td._end=true;
    _td._go =true;
  }

  friend class ExternalLock<ExternalLockTestClass>;
  Mutex          _mutex;
  TestThreadData _td;
  Thread         _t;
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::ExternalLockTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/ExternalLock");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// try single locking
template<>
template<>
void testObj::test<1>(void)
{
  _t.start();
  // test if mutex is not-locked
  {
    TryLock tl(_mutex);
    ensure( tl.trylock() );
  }

  // now this is locked
  _td._go=true;
  usleep(100*1000);
  // tryLock() should fail now
  {
    TryLock tl(_mutex);
    ensure( !tl.trylock() );
  }
}

// should pass without problems :)
template<>
template<>
void testObj::test<2>(void)
{
  const ExternalLock<ExternalLockTestClass> el(*this);
  // this does nothing
  el.doNothing();
  el.doNothing();
}

} // namespace tut


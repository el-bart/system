/*
 * GlobalInit.t.cpp
 *
 */
#include <tut.h>
#include <cassert>

#include "System/GlobalInit.hpp"
#include "System/AtExit.hpp"

using namespace System;

namespace
{

enum State
{
  STATE_UNUSED,
  STATE_INITIALIZED,
  STATE_DEINITIALIZED
};

State g_test1=STATE_UNUSED;

struct TestResults: public AtExitResourceDeallocator
{
  virtual void deallocate(void)
  {
    tut::ensure("test 1 failed", g_test1!=STATE_INITIALIZED);
  }
}; // struct Test

struct TestClass
{
  TestClass(void)
  {
    static bool init=false;
    if(!init)
    {
      AtExit::TDeallocPtr test(new TestResults);
      AtExit::registerDeallocator(test);
      init=true;
    }
  }
};

typedef tut::test_group<TestClass> factory;
typedef factory::object testObj;

factory tf("System/GlobalInit");
} // unnamed namespace


namespace tut
{

template<>
template<>
void testObj::test<1>(void)
{
}

template<>
template<>
void testObj::test<2>(void)
{
}

template<>
template<>
void testObj::test<3>(void)
{
}

template<>
template<>
void testObj::test<4>(void)
{
}

template<>
template<>
void testObj::test<5>(void)
{
}

template<>
template<>
void testObj::test<6>(void)
{
}

template<>
template<>
void testObj::test<7>(void)
{
}

template<>
template<>
void testObj::test<8>(void)
{
}

template<>
template<>
void testObj::test<9>(void)
{
}

template<>
template<>
void testObj::test<10>(void)
{
}

template<>
template<>
void testObj::test<11>(void)
{
}

template<>
template<>
void testObj::test<12>(void)
{
}

} // namespace tut

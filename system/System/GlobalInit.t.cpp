/*
 * GlobalInit.t.cpp
 *
 * NOTE: due to the nature of atexit() and related elements these tests, in
 *       most of the cases, only registe handles that will check proper
 *       conditions when program will quit, therefore if something's wrong
 *       usually asseration will fail uppon exit.
 */
#include <tut.h>
#include <boost/lexical_cast.hpp>
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
  STATE_UNINITIALIZED
};

struct TestResults: public AtExitResourceDeallocator
{
  TestResults(int n, State *s):
    n_(n),
    s_(s)
  {
    tut::ensure("state cannot be NULL", s_!=NULL);
  }

  virtual void deallocate(void)
  {
    assert(s_!=NULL);
    tut::ensure( (boost::lexical_cast<std::string>(n_)+"#test failed").c_str(), *s_!=STATE_INITIALIZED);
  }

private:
  int    n_;
  State *s_;
}; // struct TestResults


struct TestClass
{
  void registerCheck(int n, State *s) const
  {
    AtExit::TDeallocPtr test( new TestResults(n, s) );
    AtExit::registerDeallocator(test);
  }
};

typedef tut::test_group<TestClass> factory;
typedef factory::object testObj;

factory tf("System/GlobalInit");
} // unnamed namespace


namespace tut
{

// self-test 1
template<>
template<>
void testObj::test<1>(void)
{
  static State s=STATE_INITIALIZED;
  registerCheck(1, &s);
  s=STATE_UNUSED;
}

// self-test 2
template<>
template<>
void testObj::test<2>(void)
{
  static State s=STATE_INITIALIZED;
  registerCheck(2, &s);
  s=STATE_UNINITIALIZED;
}

namespace
{
static State g_stateNormal=STATE_UNUSED;

struct TestNormal
{
  static void init(void)
  {
    g_stateNormal=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateNormal=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
// test regular initialization/uninitialization
template<>
template<>
void testObj::test<3>(void)
{
  registerCheck(3, &g_stateNormal);
  GlobalInit<TestNormal> tmp;
}

namespace
{
static State g_stateExceptionOnInit=STATE_UNUSED;

struct TestExceptionOnInit
{
  static void init(void)
  {
    throw std::runtime_error("simulated error when init() is called");
  }
  static void uninit(void)
  {
    tut::fail("uninit() called when init() failed");
  }
};
} // unnamed namespace
// test if deinit is not called when exception is thrown in c-tor
template<>
template<>
void testObj::test<4>(void)
{
  registerCheck(4, &g_stateExceptionOnInit);
  try
  {
    GlobalInit<TestExceptionOnInit> tmp;
    fail("c-tor does not call init() at all");
  }
  catch(const std::runtime_error &)
  {
    // this is expected
  }
}

namespace
{
static State g_stateCopyCtor=STATE_UNUSED;

struct TestCopyCtor
{
  static void init(void)
  {
    ensure_equals("invalid initial state (init() not called or calledmultiple times)",
                  g_stateCopyCtor, STATE_UNUSED);
    g_stateCopyCtor=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateCopyCtor=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
template<>
template<>
void testObj::test<5>(void)
{
  registerCheck(5, &g_stateCopyCtor);
  GlobalInit<TestCopyCtor> tmp1;
  GlobalInit<TestCopyCtor> tmp2(tmp1);
}

namespace
{
static State g_stateAssignment=STATE_UNUSED;

struct TestAssignment
{
  static void init(void)
  {
    ensure_equals("invalid initial state (init() not called or calledmultiple times)",
                  g_stateAssignment, STATE_UNUSED);
    g_stateAssignment=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateAssignment=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
// test assignment
template<>
template<>
void testObj::test<6>(void)
{
  registerCheck(6, &g_stateAssignment);
  GlobalInit<TestAssignment> tmp1;
  GlobalInit<TestAssignment> tmp2;
  tmp2=tmp1;
}

namespace
{
static State g_stateMultipleInstances=STATE_UNUSED;

struct TestMultipleInstances
{
  static void init(void)
  {
    ensure_equals("invalid initial state (init() not called or calledmultiple times)",
                  g_stateMultipleInstances, STATE_UNUSED);
    g_stateMultipleInstances=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateMultipleInstances=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
// test multiple, independent instances
template<>
template<>
void testObj::test<7>(void)
{
  registerCheck(7, &g_stateMultipleInstances);
  GlobalInit<TestMultipleInstances> tmp1;
  GlobalInit<TestMultipleInstances> tmp2;
}

namespace
{
static State g_stateSelfAssignment=STATE_UNUSED;

struct TestSelfAssignment
{
  static void init(void)
  {
    ensure_equals("invalid initial state (init() not called or calledmultiple times)",
                  g_stateSelfAssignment, STATE_UNUSED);
    g_stateSelfAssignment=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateSelfAssignment=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
// test selft assignment
template<>
template<>
void testObj::test<8>(void)
{
  registerCheck(8, &g_stateSelfAssignment);
  GlobalInit<TestSelfAssignment> tmp;
  tmp=tmp;
}

namespace
{
static State g_stateInitLast=STATE_UNUSED;

struct TestInitLast
{
  static void init(void)
  {
    g_stateInitLast=STATE_INITIALIZED;
  }
  static void uninit(void)
  {
    g_stateInitLast=STATE_UNINITIALIZED;
  }
};
} // unnamed namespace
// test if uninit is NOT called when local object is destroyed
template<>
template<>
void testObj::test<9>(void)
{
  ensure_equals("invalid initial state", g_stateInitLast, STATE_UNUSED);
  {
    GlobalInit<TestInitLast> tmp;
    ensure_equals("not initialized", g_stateInitLast, STATE_INITIALIZED);
  }
  ensure_equals("uninitialized too fast", g_stateInitLast, STATE_INITIALIZED);
}

} // namespace tut

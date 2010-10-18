/*
 * testset1.t.cpp
 *
 * some example test set for test application.
 *
 */
#include <tut/tut.hpp>

// NOTE: a little magic goes here in order to provide own assert() declaration
struct AssertionFailed
{
}; // struct AssertionFailed
#include <cassert>
#undef assert
bool g_useAssert;
#define assert(expr) do { if( g_useAssert && !(expr) ) throw AssertionFailed(); } while(0)
#include "System/OneInstanceAtOnce.hpp"
#undef assert

using namespace System;

namespace
{
struct TestClass
{
};

typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;

factory tf("System/OneInstanceAtOnce");
} // unnamed namespace


namespace tut
{

// test creating single instance
template<>
template<>
void testObj::test<1>(void)
{
  g_useAssert=true;
  OneInstanceAtOnce<TestClass> tmp;
}

// test creating multiple instances one after another
template<>
template<>
void testObj::test<2>(void)
{
  g_useAssert=true;
  {
    OneInstanceAtOnce<TestClass> tmp;
  }
  {
    OneInstanceAtOnce<TestClass> tmp;
  }
}

// test creating second instance in debug mode
template<>
template<>
void testObj::test<3>(void)
{
  g_useAssert=true;
  OneInstanceAtOnce<TestClass> tmp1;
  try
  {
    OneInstanceAtOnce<TestClass> tmp2;
    fail("asseration didn't failed for the second instance");
  }
  catch(const AsserationFailed &)
  {
    // this is expected
  }
}

// test creating second instance in release mode
template<>
template<>
void testObj::test<4>(void)
{
  g_useAssert=false;
  OneInstanceAtOnce<TestClass> tmp1;
  try
  {
    OneInstanceAtOnce<TestClass> tmp2;
    fail("exception not thrown for the second instance");
  }
  catch(const std::logic_error &)
  {
    // this is expected
  }
}

} // namespace tut

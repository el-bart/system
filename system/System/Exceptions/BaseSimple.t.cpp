/*
 * BaseSimple.t.cpp
 *
 */
#include <tut.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <cassert>

#include "System/Exceptions/BaseSimple.hpp"

namespace System
{
namespace Exceptions
{

struct BaseSimpleTestData
{
};

} // namespace Exceptions
} // namespace System


namespace tut
{
typedef System::Exceptions::BaseSimpleTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Exceptions/BaseSimple");
}

using namespace std;
using namespace System;
using namespace System::Exceptions;

namespace tut
{

namespace
{
struct MyException: public BaseSimple<MyException, std::logic_error>
{
  template<typename T>
  MyException(const T &t):
    BaseSimple<MyException, std::logic_error>(t)
  {
  }
}; // struct MyException

const char *someStr="hello world!";
} // unnamed namespace

// test creating an instance
template<>
template<>
void testObj::test<1>(void)
{
  const MyException me("hello world!");
}

// test what() method
template<>
template<>
void testObj::test<2>(void)
{
  const MyException me(someStr);
  ensure_equals("invalid string", me.what(), string(someStr) );
}

// test whatAsStr() method
template<>
template<>
void testObj::test<3>(void)
{
  const MyException me(someStr);
  ensure_equals("invalid string", me.whatAsStr(), someStr);
}

// test for base class
template<>
template<>
void testObj::test<4>(void)
{
  const MyException  me(someStr);
  const logic_error &base=me;   // this line must compile
  base.what();                  // this suppress warning from compiler
}

// check backtrace presence
template<>
template<>
void testObj::test<5>(void)
{
  const MyException  me(someStr);
  const Backtrace   &bt=me.getBacktrace();
  ensure("backtrace is too short", bt.size()>3);
}

} // namespace tut


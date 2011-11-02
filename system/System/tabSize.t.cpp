/*
 * tabSize.t.cpp
 *
 */
#include <tut.h>
#include <cmath>

#include "System/tabSize.hpp"

using namespace System;

namespace
{
struct TestClass
{
};

typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;
factory tf("System/tabSize");
}

namespace tut
{

// check size of simple char array
template<>
template<>
void testObj::test<1>(void)
{
  const char t[]="abc";
  ensure_equals("invalid string length", tabSize(t), 4);
}

// test size of array, which elements are of non-1B size
template<>
template<>
void testObj::test<2>(void)
{
  long t[13];
  ensure_equals("invalid length of array of longs", tabSize(t), 13);
}

} // namespace tut

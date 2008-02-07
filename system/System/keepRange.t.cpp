/*
 * keepRange.t.cpp
 *
 */
#include <tut.h>

#include "System/keepRange.hpp"

namespace System
{

struct KeepRangeTestClass
{
};

} // namespace System


namespace tut
{
typedef System::KeepRangeTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/keepRange");
}

using namespace System;

namespace tut
{

// test range match
template<>
template<>
void testObj::test<1>(void)
{
  ensure( keepRange(12, 1,100)==12 );
  const int v  =12;
  const int min=10;
  const int max=20;
  ensure( keepRange(v, min,max)==v );
}

// test lower bound
template<>
template<>
void testObj::test<2>(void)
{
  ensure( keepRange(10, 10,20)==10 );
  ensure( keepRange(9,  10,20)==10 );
}

// test upper bound
template<>
template<>
void testObj::test<3>(void)
{
  ensure( keepRange(20, 10,20)==20 );
  ensure( keepRange(21, 10,20)==20 );
}

} // namespace tut


/*
 * Average.t.cpp
 *
 */
#include <tut.h>
#include <list>

#include "System/Math/Average.hpp"
#include "System/Math/arraySumFastFP.hpp"
#include "System/Math/arraySumPrecFP.hpp"

using namespace std;
using namespace System::Math;

namespace
{

struct TestClass
{
};

typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;
factory tf("System/Math/Average");
}


namespace tut
{

// test normal instance
template<>
template<>
void testObj::test<1>(void)
{
  list<float> l;
  l.push_back(2);
  l.push_back(4);
  //Average<float> a( l.begin(), l.end() );
  typedef Average<float, list<float>::const_iterator, arraySumFastFP> Avg;
  Avg a( l.begin(), l.end() );
}

// 
template<>
template<>
void testObj::test<2>(void)
{
}

// 
template<>
template<>
void testObj::test<3>(void)
{
}

// 
template<>
template<>
void testObj::test<4>(void)
{
}

// 
template<>
template<>
void testObj::test<5>(void)
{
}

} // namespace tut


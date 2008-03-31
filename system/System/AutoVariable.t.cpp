/*
 * AutoVariable.t.cpp
 *
 */
#include <tut.h>

#include "System/AutoVariable.hpp"

namespace System
{

struct AutoVariableTestData
{
  struct TestDataHolder
  {
    typedef int TValue;
    TestDataHolder(void):
      _v(-1)
    {
    }
    explicit TestDataHolder(TValue v):
      _v(v)
    {
    }
    TValue  get(void) const
    {
      return _v;
    }
    void dealocate(void)
    {
      _v=-1;
    }
    int _v;     // -1 means: no-ownership
  }; // struct TestDataHolder

  typedef AutoVariable<TestDataHolder> TestAV;

  AutoVariableTestData(void):
    _av1(1),
    _av2(2)
  {
  }

  TestAV _av1;
  TestAV _av2;
}; // struct AutoVariableTestData

} // namespace System


namespace tut
{
typedef System::AutoVariableTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/AutoVariable");
}

using namespace System;

namespace tut
{

// test if both objects were build are file.
template<>
template<>
void testObj::test<1>(void)
{
  ensure( _av1.get()==1 );
  ensure( _av2.get()==2 );
}


// check get() and operator()
template<>
template<>
void testObj::test<2>(void)
{
  ensure( _av1.isInitialized() );
  ensure( _av2.isInitialized() );

  TestAV notInit;
  ensure( !notInit.isInitialized() );
}

// isInitialized() test
template<>
template<>
void testObj::test<3>(void)
{
  ensure( _av1.isInitialized() );
  ensure( _av2.isInitialized() );
  _av1.reset(-1);
  _av2.reset(-1);
  ensure( !_av1.isInitialized() );
  ensure( !_av2.isInitialized() );
}

// ownership passing
template<>
template<>
void testObj::test<4>(void)
{
  TestAV a;
  int tmp=_av1.get();
  a      =_av1;     // ownership passing
  ensure( !_av1.isInitialized() );
  ensure( _av1.get()!=a.get() );
  ensure( a.get()==tmp );
}

// reseting and releasing
template<>
template<>
void testObj::test<5>(void)
{
  TestAV a;
  int    tmp=_av1.get();
  a.reset( _av1.release() );
  ensure( !_av1.isInitialized() );
  ensure( a.get()==tmp );
}

// test copy-constructor
template<>
template<>
void testObj::test<6>(void)
{
  TestAV a(_av1);
  ensure(     a.isInitialized() );
  ensure( !_av1.isInitialized() );
}

// test default constructor
template<>
template<>
void testObj::test<7>(void)
{
  TestAV t;                 // should compie fine
  ensure( t.get()==-1 );    // no object should be allocated
}

// reset to another value
template<>
template<>
void testObj::test<8>(void)
{
  TestAV t;
  ensure( !t.isInitialized() );

  t.reset(7);
  ensure( t.get()==7 );
  ensure( t.isInitialized() );

  t.reset(-1);
  ensure( !t.isInitialized() );
}

} // namespace tut


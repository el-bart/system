/*
 * IterableEnum.t.cpp
 *
 * test set for Enum.
 *
 */
#include <tut.h>

#include "System/IterableEnum.hpp"

namespace System
{

struct IterableEnumTestData
{
  struct MyEnum
  {
    typedef enum
    {
      A=10,
      B=11,
      C=12,
      D=13,
      E=14
    } Type;
    enum { Min=A };
    enum { Max=E };
  };

  typedef System::IterableEnum<MyEnum> TestEnum;
  typedef TestEnum::BType              TestEnumBase;

  IterableEnumTestData(void):
    _te( TestEnum::A )
  {
  }

  TestEnum _te;
};

} // namespace System


namespace tut
{
typedef System::IterableEnumTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/IterableEnum");
}



namespace tut
{

// Class<->Enum comparison
template<>
template<>
void testObj::test<1>(void)
{
  _te = TestEnum::B;
  ensure( "comparing (==) System::Enum with enum value failed",
          _te==TestEnum::B );
  ensure( "comparing (!=) System::Enum with enum value failed",
          _te!=TestEnum::A );
}

// Class<->Class comaprison
template<>
template<>
void testObj::test<2>(void)
{
  TestEnum other=TestEnum::C;
  _te=TestEnum::C;
  ensure( "comparison between two System::Enum failed",
          _te==other );
}


// Assignment tests
template<>
template<>
void testObj::test<3>(void)
{
  TestEnum other1=_te;
  TestEnum other2=TestEnum::B;

  other1=TestEnum::A;
  other2=other1;
  ensure( "assignment to System::Enum from System::Enum failed",
          other1==other2 );
}

// convertion to long
template<>
template<>
void testObj::test<4>(void)
{
  long x;

  x=_te.toLong();
  ensure(x==10);

  _te=TestEnum::C;
  x=_te.toLong();
  ensure(x==12);
}

// test creating from base
template<>
template<>
void testObj::test<5>(void)
{
  TestEnumBase base   =_te;
  TestEnum     derived=base;
  ensure( derived.toLong()==base.toLong() );
}

// test assigning from base
template<>
template<>
void testObj::test<6>(void)
{
  TestEnum     derived=_te;
  TestEnumBase base2  =TestEnumBase::D;
  derived=base2;
  ensure( derived.toLong()==base2.toLong() );
}

// test assiging from pure enum
template<>
template<>
void testObj::test<7>(void)
{
  TestEnum derived=_te;
  derived=TestEnum::D;
  ensure( derived.toLong()==TestEnum::D );
}

// test comparing to self
template<>
template<>
void testObj::test<8>(void)
{
  ensure(   _te==_te  );
  ensure( !(_te!=_te) );
}

// test comparing to base
template<>
template<>
void testObj::test<9>(void)
{
  TestEnumBase base=_te;
  ensure(   _te==base  );
  ensure( !(_te!=base) );
}

// test begin iterator
template<>
template<>
void testObj::test<10>(void)
{
  ensure( *_te.begin()==TestEnum::A );
  ensure( *_te.begin()==10          );
}

// test end iterator
template<>
template<>
void testObj::test<11>(void)
{
  ensure( *_te.end()==TestEnum::E+1 );
  ensure( *_te.end()==14+1          );
}

// test getting size of enum-container
template<>
template<>
void testObj::test<12>(void)
{
  ensure( _te.size()==5 );
  ensure( _te.size()==TestEnum::Size );
}

// const_iterator construction (default)
template<>
template<>
void testObj::test<13>(void)
{
  TestEnum::const_iterator it;
  ensure( *it==TestEnum::A );
}

// const_iterator non-default construction
template<>
template<>
void testObj::test<14>(void)
{
  TestEnum::const_iterator it( TestEnum::B );
  ensure( *it==TestEnum::B );
}

// test equality operator
template<>
template<>
void testObj::test<15>(void)
{
  TestEnum::const_iterator it;
  ensure(it==it);
}

// test inequality operator
template<>
template<>
void testObj::test<16>(void)
{
  TestEnum::const_iterator it;
  ensure( !(it!=it) );
}

// pre-incrementation test
template<>
template<>
void testObj::test<17>(void)
{
  TestEnum::const_iterator it_prev;
  TestEnum::const_iterator it =it_prev;
  TestEnum::const_iterator out=++it;
  ensure( it_prev!=it  );
  ensure( it     ==out );
}

// post-incrementation test
template<>
template<>
void testObj::test<18>(void)
{
  TestEnum::const_iterator it_prev;
  TestEnum::const_iterator it =it_prev;
  TestEnum::const_iterator out=it++;
  ensure( it_prev!=it  );
  ensure( it_prev==out );
}

// dereference operator test
template<>
template<>
void testObj::test<19>(void)
{
  TestEnum::const_iterator it;
  ensure(*it==10);
  ++it;
  ensure(*it==11);
  it++;
  ensure(*it==12);
}

// test if range is valid
template<>
template<>
void testObj::test<20>(void)
{
  TestEnum::const_iterator it;
  for(long i=10; i<=14; ++i)
    ++it;   // should not rise assert
  ensure(*it==15);
}

// test iteration throught elements;
template<>
template<>
void testObj::test<21>(void)
{
  long v=static_cast<long>(TestEnum::Min);
  for(TestEnum::const_iterator it=_te.begin();
      it!=_te.end();
      ++it)
  {
    ensure(*it==v);
    ++v;
  }
}

} // namespace tut


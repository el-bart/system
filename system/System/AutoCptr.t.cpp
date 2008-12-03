/*
 * AutoCptr.t.cpp
 *
 */
#include <tut.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <cassert>

#include "System/AutoCptr.hpp"

namespace System
{

struct AutoCptrTestData
{
  typedef AutoCptr<void> ACP;

  AutoCptrTestData(void):
    _ap1( malloc(2)      ),
    _ap2( malloc(4*1024) )
  {
    tut::ensure( _ap1.get()!=NULL );
    tut::ensure( _ap2.get()!=NULL );
  }

  ACP _ap1;
  ACP _ap2;
};

} // namespace System


namespace tut
{
typedef System::AutoCptrTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/AutoCptr");
}

using namespace System;

namespace tut
{

// check read/write from small memory pointer.
template<>
template<>
void testObj::test<1>(void)
{
  char *p1=static_cast<char*>( _ap1.get() );
  for(int i=0; i<2; ++i)
  {
    *(p1+i)='x';            // write.
    ensure( *(p1+i)=='x' ); // stupid, but reads. ;)
  }
}

// test r/w for biger memory part pointer.
template<>
template<>
void testObj::test<2>(void)
{
  char *p2=static_cast<char*>( _ap2.get() );
  for(int i=0; i<4*1024; ++i)
  {
    *(p2+i)='x';            // write.
    ensure( *(p2+i)=='x' ); // stupid, but reads. ;)
  }
}

// test for memory leaks by allocating a lot of memory
template<>
template<>
void testObj::test<3>(void)
{
  const size_t oneMB=1024*1024;
  const size_t size =300*oneMB;     // 300MB
  const size_t off  =size-oneMB;    // next to last MB
  assert(size>oneMB);
  for(size_t i=0; i<10; ++i)
  {
    ACP p( malloc(size) );          // allocate and catch.
    ensure( p.get()!=NULL );        // test if it passed.
    // write something to the memory
    char *ptr=static_cast<char*>( p.get() );
    memset( ptr+off, 0, oneMB );
    // here goes release.
  }
}

} // namespace tut


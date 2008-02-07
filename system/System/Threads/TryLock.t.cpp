/*
 * TryLock.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/TryLock.hpp"


namespace System
{
namespace Threads
{

struct TryLockTestClass
{
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::TryLockTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/TryLock");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// try constructor/destructor
template<>
template<>
void testObj::test<1>(void)
{
  Mutex   m;
  TryLock tl(m);
}

// try single locking
template<>
template<>
void testObj::test<2>(void)
{
  Mutex   m;
  TryLock tl(m);
  ensure( tl.trylock()==true );    // no reason to fail
  ensure( tl.trylock()==true );    // and should be recurrent
}

// try if TryLock does not leak
template<>
template<>
void testObj::test<3>(void)
{
  Mutex m;
  for(unsigned int i=0; i<4096; ++i)
    TryLock tl(m);
}

} // namespace tut


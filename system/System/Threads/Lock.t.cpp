/*
 * Lock.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/Lock.hpp"


namespace System
{
namespace Threads
{

struct LockTestClass
{
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::LockTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/Lock");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// try single locking
template<>
template<>
void testObj::test<1>(void)
{
  Mutex m;
  Lock  l(m);
}

// try if Lock does not leak
template<>
template<>
void testObj::test<2>(void)
{
  Mutex m;
  for(unsigned int i=0; i<4096; ++i)
    Lock l(m);
}

} // namespace tut


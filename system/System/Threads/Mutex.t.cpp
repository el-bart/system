/*
 * Mutex.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/Mutex.hpp"


namespace System
{
namespace Threads
{

struct MutexTestClass
{
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::MutexTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/Mutex");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// at this point mutex leaks can only be checked...
template<>
template<>
void testObj::test<1>(void)
{
  for(unsigned int i=0; i<4096; ++i)
    Mutex();
}

} // namespace tut


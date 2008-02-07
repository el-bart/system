/*
 * Condition.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/Condition.hpp"


namespace System
{
namespace Threads
{

struct ConditionTestClass
{
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::ConditionTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/Condition");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// test if conditional variables doesn't leak
template<>
template<>
void testObj::test<1>(void)
{
  for(unsigned int i=0; i<4096; ++i)
    Condition();
}

} // namespace tut


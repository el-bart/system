/*
 * ScopedCustomPointer.t.cpp
 *
 */
#include <tut.h>

#include "System/ScopedCustomPointer.hpp"

namespace System
{

struct ScopedCustomPointerTestClass
{
};

} // namespace System


namespace tut
{
typedef System::ScopedCustomPointerTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/ScopedCustomPointer");
}

using namespace System;

namespace tut
{

// 
template<>
template<>
void testObj::test<1>(void)
{
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

// 
template<>
template<>
void testObj::test<6>(void)
{
}

// 
template<>
template<>
void testObj::test<7>(void)
{
}

// 
template<>
template<>
void testObj::test<8>(void)
{
}

// 
template<>
template<>
void testObj::test<9>(void)
{
}

// 
template<>
template<>
void testObj::test<10>(void)
{
}

} // namespace tut

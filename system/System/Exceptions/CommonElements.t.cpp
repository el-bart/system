/*
 * CommonElements.t.cpp
 *
 */
#include <tut/tut.hpp>

#include "System/Exceptions/CommonElements.hpp"

using namespace System::Exceptions;

namespace
{
struct TestClass
{
  CommonElements ce_;
};

typedef TestClass                  TestClass;
typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;

factory tf("System/Exceptions/CommonElements");
} // unnamed namespace


namespace tut
{

// concatenate 2 args
template<>
template<>
void testObj::test<1>(void)
{
  ensure_equals("invalid concatenataion",
                ce_.cc("a", "b"), "ab");
}

// concatenate 3 arguments
template<>
template<>
void testObj::test<2>(void)
{
  ensure_equals("invalid concatenataion",
                ce_.cc("a", "b", "c"), "abc");
}

// concatenate 4 arguments
template<>
template<>
void testObj::test<3>(void)
{
  ensure_equals("invalid concatenataion",
                ce_.cc("a", "b", "c", "d"), "abcd");
}

// concatenate 5 arguments
template<>
template<>
void testObj::test<4>(void)
{
  ensure_equals("invalid concatenataion",
                ce_.cc("a", "b", "c", "d", "e"), "abcde");
}

// concatenate 6 arguments
template<>
template<>
void testObj::test<5>(void)
{
  ensure_equals("invalid concatenataion",
                ce_.cc("a", "b", "c", "d", "e", "f"), "abcdef");
}

} // namespace tut

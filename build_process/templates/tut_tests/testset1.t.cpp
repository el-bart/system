/*
 * testset1.t.cpp
 *
 * some example test set for test application.
 *
 */
#include <tut.h>

namespace UserNamespace
{

struct SomeTestClass
{
  bool isZero(int v) const
  {
    return v==0;
  }
};

} // namespace UserNamespace


namespace tut
{
typedef UserNamespace::SomeTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("UserNamespace/Some");
}



namespace tut
{

template<>
template<>
void testObj::test<1>(void)
{
  ensure(  isZero(0) );
  ensure( !isZero(2) );
}

} // namespace tut


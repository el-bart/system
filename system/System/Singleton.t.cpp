/*
 * Singleton.t.cpp
 *
 */
#include <tut.h>

#include "System/Singleton.hpp"

namespace
{
  struct MySingleType
  {
    MySingleType(void):
      _cnt(0)
    {
    }

    void inc(void)
    {
      ++_cnt;
    }

    int get(void) const
    {
      return _cnt;
    }
  private:
    int _cnt;
  }; // struct MySingleType
} // unnamed namespace


namespace System
{

struct SingletonTestClass
{
};

} // namespace System


namespace tut
{
typedef System::SingletonTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Singleton");
}

typedef System::Singleton<MySingleType> TestSingleton;

namespace tut
{

template<>
template<>
void testObj::test<1>(void)
{
  ensure( TestSingleton::get()->get()==0 );

  TestSingleton::get()->inc();
  ensure( TestSingleton::get()->get()==1 );

  TestSingleton::get()->inc();
  ensure( TestSingleton::get()->get()==2 );
}


template<>
template<>
void testObj::test<2>(void)
{
  TestSingleton::get()->inc();
  ensure( TestSingleton::get()->get()==3 );
}

} // namespace tut


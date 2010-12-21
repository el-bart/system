/*
 * DynamicObject.t.cpp
 *
 */
#include <tut/tut.hpp>
#include <dlfcn.h>

#include "System/Plugins/DynamicObject.hpp"

using namespace System::Plugins;

namespace
{
struct TestClass
{
  TestClass(void):
    h_( openShared() )
  {
  }

  void *openShared(void)
  {
    dlerror();
    void *h=dlopen("testdata/sharedobj.so", RTLD_LOCAL|RTLD_LAZY);
    if(h==NULL)
      tut::fail( dlerror() );
    return h;
  }

  DynamicObject h_;
};

typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;

factory tf("System/Plugins/DynamicObject");
} // unnamed namespace


namespace tut
{

// test exception when NULL-pointer is passed
template<>
template<>
void testObj::test<1>(void)
{
  try
  {
    DynamicObject h(NULL);
    fail("c-tor didn't failed for NULL handle");
  }
  catch(const System::ExceptionPointerIsNULL &)
  {
    // this is expected
  }
}

// try reading global variable
template<>
template<>
void testObj::test<2>(void)
{
  int *ptr=h_.getSymbol<int*>("g_int");
  ensure("NULL pointer", ptr!=NULL);
  ensure_equals("invalid value", *ptr, 42);
}

// try reading non-existing variable
template<>
template<>
void testObj::test<3>(void)
{
  try
  {
    h_.getSymbol<int*>("non_existing_symbol");
    fail("reading non-existing symbol didn't failed");
  }
  catch(const ExceptionCannotReadSymbol &)
  {
    // this is expected
  }
}

// try reading some function symbol
template<>
template<>
void testObj::test<4>(void)
{
  long (*f)(const char*)=h_.getSymbol<long(*)(const char*)>("testFunctionSymbol");
  ensure("NULL pointer", f!=NULL);
  ensure_equals("invalid call", (*f)("alice has a cat"), 15);
}

// reading non-exisitng function pointer
template<>
template<>
void testObj::test<5>(void)
{
  try
  {
    h_.getSymbol<int(*)(int)>("non_existing_symbol");
    fail("reading non-existing symbol didn't failed");
  }
  catch(const ExceptionCannotReadSymbol &)
  {
    // this is expected
  }
}

} // namespace tut

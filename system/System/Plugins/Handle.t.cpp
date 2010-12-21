/*
 * Handle.t.cpp
 *
 */
#include <tut/tut.hpp>
#include <dlfcn.h>

#include "System/Plugins/Handle.hpp"

using namespace System::Plugins;

namespace
{
struct TestClass
{
  void *openShared(void)
  {
    dlerror();
    void *h=dlopen("testdata/sharedobj.so", RTLD_LOCAL|RTLD_LAZY);
    if(h==NULL)
      tut::fail( dlerror() );
    return h;
  }
};

typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;

factory tf("System/Plugins/Handle");
} // unnamed namespace


namespace tut
{

// test NULL pointer
template<>
template<>
void testObj::test<1>(void)
{
  try
  {
    Handle h(NULL);
    fail("c-tor didn't failed for NULL");
  }
  catch(const System::ExceptionPointerIsNULL &)
  {
    // this is expected
  }
}

// test non-NULL pointer
template<>
template<>
void testObj::test<2>(void)
{
  Handle h( openShared() );
}

// test accessor method
template<>
template<>
void testObj::test<3>(void)
{
  Handle h( openShared() );
  ensure("pointer is NULL", h.get()!=NULL );    // compile-check, in fact
}

} // namespace tut

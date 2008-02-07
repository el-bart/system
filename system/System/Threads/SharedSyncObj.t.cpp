/*
 * SharedSyncObj.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/SharedSyncObj.hpp"

// test obj
namespace
{
class SyncMe
{
public:
  SyncMe(void):
    i(0)
  {
  }
  void inc(void)
  {
    ++i;
  }
  int get(void) const
  {
    return i;
  }
private:
  int i;
}; // struct SyncMe

struct MySyncObj: public System::Threads::SyncObj<SyncMe>
{
  MySyncObj(void)
  {
    init(&_sm);
  }

private:
  SyncMe _sm;
}; // struct MySyncObj
} // unnamed namespace


namespace System
{
namespace Threads
{

struct SharedSyncObjTestClass: public SharedSyncObj<MySyncObj>
{
  SharedSyncObjTestClass(void):
    SharedSyncObj<MySyncObj>( new MySyncObj )
  {
  }
}; // struct SharedSyncObjTestClass

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::SharedSyncObjTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/SharedSyncObj");
}

using namespace System;
using namespace System::Threads;


namespace tut
{

// test basic synchronization in non-const mode
template<>
template<>
void testObj::test<1>(void)
{
  SharedSyncObjTestClass sotc;
  // critical section
  {
    SharedSyncObjTestClass::ExtLock el(sotc);        // our ExtLock
    ensure( sotc(el)->get()==0 );
    sotc(el)->inc();
    ensure( sotc(el)->get()==1 );
  }
}

// test basic synchronization in const mode
template<>
template<>
void testObj::test<2>(void)
{
  SharedSyncObjTestClass sotc;
  // critical section
  {
    SharedSyncObjTestClass::ExtLock  el(sotc);      // our ExtLock
    const SharedSyncObjTestClass    &csotc=sotc;    // const version
    ensure( csotc(el)->get()==0 );
    sotc(el)->inc();
    ensure( csotc(el)->get()==1 );
  }
}

// test copy construction
template<>
template<>
void testObj::test<3>(void)
{
  SharedSyncObjTestClass sotc1;
  SharedSyncObjTestClass sotc2(sotc1);
  // critical section
  {
    SharedSyncObjTestClass::ExtLock  el1(sotc1);    // our ExtLock
    SharedSyncObjTestClass::ExtLock  el2(sotc2);    // our ExtLock
    ensure( sotc1(el1)==sotc2(el2) );               // address should match
  }
}

// test assignment operator
template<>
template<>
void testObj::test<4>(void)
{
  SharedSyncObjTestClass sotc1;
  SharedSyncObjTestClass sotc2;
  sotc2=sotc1;
  // critical section
  {
    SharedSyncObjTestClass::ExtLock  el1(sotc1);    // our ExtLock
    SharedSyncObjTestClass::ExtLock  el2(sotc2);    // our ExtLock
    ensure( sotc1(el1)==sotc2(el2) );               // address should match
  }
}

} // namespace tut


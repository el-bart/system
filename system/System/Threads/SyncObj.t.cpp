/*
 * SyncObj.t.cpp
 *
 */
#include <tut.h>
#include <unistd.h>

#include "System/Threads/SyncObj.hpp"

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
} // unnamed namespace


namespace System
{
namespace Threads
{

struct SyncObjTestClass: public SyncObj<SyncMe>
{
  SyncObjTestClass(void)
  {
    init(&_sm);
  }

private:
  SyncMe _sm;
};

} // namespace Threads
} // namespace System


namespace tut
{
typedef System::Threads::SyncObjTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Threads/SyncObj");
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
  SyncObjTestClass sotc;
  // critical section
  {
    SyncObjTestClass::ExtLock el(sotc); // our ExtLock
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
  SyncObjTestClass sotc;
  // critical section
  {
    SyncObjTestClass::ExtLock el(sotc); // our ExtLock
    const SyncObjTestClass &csotc=sotc; // const version
    ensure( csotc(el)->get()==0 );
    sotc(el)->inc();
    ensure( csotc(el)->get()==1 );
  }
}

} // namespace tut


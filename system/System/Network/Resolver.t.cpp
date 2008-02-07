/*
 * Resolver.t.cpp
 *
 */
#include <tut.h>

#include "System/Network/Resolver.hpp"


namespace tut
{
namespace System
{
namespace Network
{

struct ResolverTestClass
{
  bool isZero(int v) const
  {
    return v==0;
  }
};

} // namespace Network
} // namespace System
} // namespace tut


namespace tut
{
typedef System::Network::ResolverTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Network/Resolver");
}


using namespace System::Network;

namespace tut
{

template<>
template<>
void testObj::test<1>(void)
{
  Address localhost("localhost", 1234);
  Address ip       ("127.0.0.1", 1234);

  ensure( "address translation failed",
          Resolver(localhost).getAddress()==ip );
}

} // namespace tut


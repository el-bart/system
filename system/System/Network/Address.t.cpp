/*
 * Address.t.cpp
 *
 */
#include <tut.h>

#include "System/Network/Address.hpp"


namespace tut
{
namespace System
{
namespace Network
{

struct AddressTestClass
{
};

} // namespace Network
} // namespace System
} // namespace tut


namespace tut
{
typedef System::Network::AddressTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Network/Address");
}



using namespace System::Network;

namespace tut
{

template<>
template<>
void testObj::test<1>(void)
{
  Address addr("1.2.3.4", 666);
  ensure( "address construction failed",
          addr.getAddressStr()=="1.2.3.4:666" );
}


template<>
template<>
void testObj::test<2>(void)
{
  Address addr1("1.2.3.4", 999);
  Address addr2=addr1;
  ensure( "address' comaprison (==) doesn't work",
          addr1==addr2 );
}


template<>
template<>
void testObj::test<3>(void)
{
  Address addr1("1.2.3.4", 969);
  Address addr2("1.1.1.1", 960);
  ensure( "address' comparison (!=) doesn't work",
          addr1!=addr2 );
}

} // namespace tut


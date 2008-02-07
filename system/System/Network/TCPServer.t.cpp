/*
 * TCPServer.t.cpp
 *
 */
#include <tut.h>

#include "System/Network/TCPServer.hpp"


namespace tut
{
namespace System
{
namespace Network
{

struct TCPServerTestClass
{
};

} // namespace Network
} // namespace System
} // namespace tut


namespace tut
{
typedef System::Network::TCPServerTestClass TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Network/TCPServer");
}



using namespace System;
using namespace System::Network;

namespace tut
{

// test if server doesn't leak resources
template<>
template<>
void testObj::test<1>(void)
{
  for(unsigned int i=0; i<4000; ++i)
    TCPServer( Address("localhost", 61333) );
}

} // namespace tut


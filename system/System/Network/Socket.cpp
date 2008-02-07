/*
 * Socket.cpp
 *
 */
#include "System/Network/Socket.hpp"


namespace System
{
namespace Network
{

Socket::Socket(int sock):
  _sock(sock)
{
}


Socket::Socket(const AutoDescriptor sock):
  _sock(sock)
{
  if( !isActive() )
    throw Exception("System::Network::Socket::Socket(): "
                    "socket is not initialized");
}

void Socket::close(void)
{
  _sock.reset();
}

} // namespace Network
} // namespace System


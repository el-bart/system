/*
 * TCPServer.cpp
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>

#include "System/AutoDescriptor.hpp"
#include "System/Network/TCPServer.hpp"
#include "System/Network/Resolver.hpp"


namespace System
{
namespace Network
{

TCPServer::TCPServer(const Address &addr, int listenQueueLen):
                Server(addr)
{
  const Address ipPort=Resolver(addr).getAddress();

  sockaddr_in sockAddr;     // our listen-on address
  sockAddr.sin_addr.s_addr=inet_addr( ipPort.getHost().c_str() );
  assert(sockAddr.sin_addr.s_addr!=INADDR_NONE);
  sockAddr.sin_family     =AF_INET;
  sockAddr.sin_port       =ipPort.getPortHTON();

  AutoDescriptor sock( socket(AF_INET, SOCK_STREAM, 0) );
  const int fd=sock.get();
  if(fd==-1)
    throw Exception("TCPServer::TCPServer(): socket() failed");

  // bind address with socket
  if( bind(fd, reinterpret_cast<sockaddr*>(&sockAddr),
           sizeof(sockAddr) )==-1 )
    throw Exception("TCPServer::TCPServer(): bind() failed");

  // begin listening on the address
  if( listen(fd, listenQueueLen)==-1 )
    throw Exception("TCPServer::TCPServer(): listen() failed");

  //
  // write down our socket info!
  //
  setSock( sock.release() );
}


Connection TCPServer::accept(void)
{
  const int fd=_sock.get();     // helper

  // accept and return connection
  sockaddr_in addrRem;
  int         addrLen=sizeof(addrRem);
  // make socket from int
  AutoDescriptor sock( ::accept(fd, reinterpret_cast<sockaddr*> (&addrRem),
                                    reinterpret_cast<socklen_t*>(&addrLen) ) );
  // and return it as connection
  return connectionFromSock(sock);
}

} // namespace Network
} // namespace System


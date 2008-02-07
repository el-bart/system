/*
 * TCPServer.hpp
 *
 * class representing server side of
 * the TCP connection.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_TCPSERVER_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_TCPSERVER_HPP_FILE

/* public header */

#include "System/Network/Server.hpp"
#include "System/Network/Connection.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

class TCPServer: public  System::Network::Server
{
public:
  // open TCP port for incomming connections on a given
  // ip:port
  //   listenQueueLen - how many host may be in queue at a time?
  TCPServer(const System::Network::Address &addr,
            int listenQueueLen=3);

  // accept and return connection.
  System::Network::Connection accept(void);
};

} // namespace Network
} // namespace System

#endif


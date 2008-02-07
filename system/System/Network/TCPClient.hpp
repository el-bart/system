/*
 * TCPClient.hpp
 *
 * client side of TCP connection.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_TCPCLIENT_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_TCPCLIENT_HPP_FILE

/* public header */

#include "System/Network/Client.hpp"



namespace System
{
namespace Network
{

class TCPClient: public  System::Network::Client
{
public:
  // connects with a given host
  TCPClient(const System::Network::Address &addr);
};

} // namespace Network
} // namespace System

#endif


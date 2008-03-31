/*
 * Server.hpp
 *
 * abstract class representing server side of
 * the connection.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_SERVER_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_SERVER_HPP_FILE

/* public header */

#include <memory>
#include <boost/noncopyable.hpp>
#include <assert.h>

#include "System/Network/Socket.hpp"
#include "System/Network/Connection.hpp"
#include "System/Network/Address.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

class Server: protected boost::noncopyable
{
public:
  inline const System::Network::Address &getAddress(void) const
  {
    return _addr;
  }

  inline bool isActive(void) const
  {
    return _sock.isActive();
  }

  // checks if connection is aviable and returns true/false.
  //   ms - timeout for waiting in milliseconds (0==infinity)
  bool waitForConnection(unsigned int ms=0);

protected:
  Server(const System::Network::Address &addr):
    _addr(addr)
  {
  }

  // this is intended to be used by derived classes
  void setSock(int sock)
  {
    assert( !_sock.isActive() );        // this should be done only once!
    System::Network::Socket sTmp(sock);
    _sock=sTmp;
  }

  // this is needed for spawning new connections
  System::Network::Connection
        connectionFromSock(System::AutoDescriptor ad);

  // these are intentionaly protected - derived clas needs to
  // change them anytime eitherway...
  System::Network::Socket        _sock; // open-port socket
  const System::Network::Address _addr; // listen address
};

} // namespace Network
} // namespace System

#endif


/*
 * Client.hpp
 *
 * abstract class representing client side of
 * the connection.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_CLIENT_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_CLIENT_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>
#include <assert.h>

#include "System/Network/Connection.hpp"
#include "System/Network/Address.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

class Client: protected boost::noncopyable
{
public:
  inline const System::Network::Address &getAddress(void) const
  {
    return _addr;
  }

  // we return pointer instead of reference,
  // beacause reference could be accidently "captured"
  // by non-reference, deactualizing our internal instance.
  inline System::Network::Connection *getConn(void) const
  {
    if( !isActive() )
      throw System::Exception("Connection::getConn(): not connected");
    return _conn.get();
  }

  inline bool isActive(void) const
  {
    return _conn->isActive();
  }

  void flush(void)
  {
    _conn->flush();
  }
  void flushRX(void)
  {
    _conn->flushRX();
  }
  void flushTX(void)
  {
    _conn->flushTX();
  }

protected:
  Client(const System::Network::Address &addr):
    _addr(addr)
  {
  }

  void setConn(int sock)                    // sets connection from sock
  {
    assert(0<=sock);
    System::Network::Socket socket(sock);   // temporary socket
    assert( _conn.get()==NULL );            // this can be done just once!
    _conn.reset( new System::Network::Connection(socket) ); // write connection
  }

  std::auto_ptr<System::Network::Connection> _conn; // our connection
  const Network::Address  _addr;            // address we're connected with
};

} // namespace Network
} // namespace System

#endif


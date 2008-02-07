/*
 * Connection.cpp
 *
 */

#include "System/Network/Connection.hpp"


namespace System
{
namespace Network
{

Connection::Connection(const Socket &sock):
    _sock( sock )
{
  const int &fd=_sock.get();      // just a helper

  _rx.reset( fdopen( dup(fd), "r") );
  if( !_rx.isInitialized() )
    throw System::Exception("System::Network::Connection(): "
                            "unable to create RX stream");

  _tx.reset( fdopen( dup(fd), "w") );
  if( !_tx.isInitialized() )
    throw System::Exception("System::Network::Connection(): "
                            "unable to create TX stream");
}

} // namespace Network
} // namespace System


/*
 * Connection.hpp
 *
 * class holding parameters for a single connection.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_CONNECTION_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_CONNECTION_HPP_FILE

/* public header */

#include <stdio.h>
#include <unistd.h>

#include "System/Network/Socket.hpp"
#include "System/AutoFILE.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

//
// class representing single connection. it can be copied
// thou it does NOT behave like a value (just like auto_ptr).
//
class Connection
{
public:
  //
  // sock - socket of a connection to hold. after creating
  //        object of this class it **owns** sock socket!
  //
  Connection(System::Network::Socket &sock);

  // returns pointer to proper transmition stream
  // (do NOT close these streams manualy!):
  inline FILE *getRXstrm(void)
  {
    return _rx;
  }
  inline FILE *getTXstrm(void)
  {
    return _tx;
  }

  inline bool isActive(void) const
  {
    return _rx.isInitialized() && _tx.isInitialized() && _sock.isActive();
  }

  // it is sometimes required to flush buffers
  inline void flush(void)
  {
    flushRX();
    flushTX();
  }
  inline void flushRX(void)
  {
    fflush( _rx.get() );
  }
  inline void flushTX(void)
  {
    fflush( _tx.get() );
  }

private:
  System::Network::Socket _sock;    // base socket
  System::AutoFILE        _rx;      // RX stream
  System::AutoFILE        _tx;      // TX stream
};

} // namespace Network
} // namespace System

#endif


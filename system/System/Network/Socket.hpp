/*
 * Socket.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_SOCKET_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_SOCKET_HPP_FILE

/* public header */

#include <unistd.h>

#include "System/AutoDescriptor.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

// forward declarations
class Server;
class Client;

//
// class representing the socket.
// note: this class does NOT behave like a value!
//
class Socket
{
public:
  inline int get(void)
  {
    return _sock.get();
  }

  inline bool isActive(void) const
  {
    return _sock.isInitialized();
  }

  void close(void);

private:
  explicit Socket(int sock=-1);
  explicit Socket(System::AutoDescriptor sock);

  // this will be needed, so that only these classes could
  // estabilish connection:
  friend class System::Network::Server;
  friend class System::Network::Client;

  System::AutoDescriptor _sock; // our socket
};

} // namespace Network
} // namespace System

#endif


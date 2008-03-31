/*
 * Server.cpp
 *
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>

#include "System/Network/Server.hpp"


namespace System
{
namespace Network
{

bool Server::waitForConnection(unsigned int ms)
{
  // helpers
  unsigned int sec =ms/1000;
  unsigned int msec=ms%1000;
  const int    fd  =_sock.get();

  // wait for connection
  struct timeval  tv    ={sec, msec};
  struct timeval *tv2use=(ms==0)?NULL:&tv;

  bool connRet=false;     // return value

  for(;;)
  {
    fd_set fds;
    int    ret;

    // wait on select for data
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    ret=select(fd+1, &fds, NULL, NULL, tv2use);

    if(ret==-1)     // error?
    {
      if(errno==EINTR)  // is it interrupt?
        continue;
      else
        throw Exception("System::Network::Server::waitForConnection(): "
                        "select() failed");
    }

    if(ret==0)      // timeout occures?
    {
      connRet=false;
      break;
    }

    if(ret==1)      // got connection?
    {
      connRet=true;
      break;
    }

    assert(!"System::Network::Server::waitForConnection(): "
            "process should never reach this");
  } // for(;;)

  return connRet;
}


Connection Server::connectionFromSock(AutoDescriptor ad)
{
  Socket     sock(ad);
  Connection conn(sock);
  return conn;
}

} // namespace Network
} // namespace System


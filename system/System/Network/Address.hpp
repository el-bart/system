/*
 * Address.hpp
 *
 * class for representing address info - IP/DNS name
 * and port of some host.
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_ADDRESS_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_ADDRESS_HPP_FILE

/* public header */

#include <string>
#include <stdio.h>
#include <netinet/in.h>
#include <boost/operators.hpp>


namespace System
{
namespace Network
{

class Address: public boost::equality_comparable<Address>
{
public:
  // addr - host address/name
  // port - host port in host byte order
  Address(const std::string &addr, unsigned short port):
    _addr(addr),
    _port(port)
  {
  }

  std::string getAddressStr(void) const
  {
    std::string str(_addr+":");
    char portStr[6];     // 65535 is max for ushort!
    sprintf(portStr, "%d", _port);
    str=str+portStr;
    return str;
  }

  // returns host name
  inline const std::string &getHost(void) const
  {
    return _addr;
  }

  // returns port in host byte order
  inline const unsigned short &getPort(void) const
  {
    return _port;
  }

  // returns port in network byte order
  inline unsigned short getPortHTON(void) const
  {
    return htons(_port);
  }

  inline bool operator==(const Address& addr) const
  {
    return getAddressStr()==addr.getAddressStr();
  }

private:
  std::string    _addr;   // IP/DNS-name of a host
  unsigned short _port;   // port on host
};

} // namespace Network
} // namespace System

#endif


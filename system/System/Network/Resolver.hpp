/*
 * Resolver.hpp
 *
 * helper class for resolving hosts via DNS.
 *
 * WARRNING: this class is NOT thread safe!
 *
 */
#ifndef INCLUDE_SYSTEM_NETWORK_RESOLVER_HPP_FILE
#define INCLUDE_SYSTEM_NETWORK_RESOLVER_HPP_FILE

/* public header */

#include <vector>
#include <string>

#include "System/Network/Address.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Network
{

class Resolver
{
public:
  class Exception: public System::Exception
  {
  public:
    Exception(const std::string &what):
      System::Exception( std::string("Resolver::Exception: ")+what )
    {
    }
    Exception(const char *what):
      System::Exception( std::string("Resolver::Exception: ")+what )
    {
    }
  }; // class Exception

  // resolves given address
  Resolver(const System::Network::Address &cInfo);

  // return address from a given posiotion
  inline const System::Network::Address &getAddress(unsigned int pos=0) const
  {
    return _addr.at(pos);
  }
  // return number of entries available
  inline unsigned int addressCount(void) const
  {
    return _addr.size();
  }

private:
  std::vector<System::Network::Address> _addr;
}; // class Resolver

} // namespace Network
} // namespace System

#endif


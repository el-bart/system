/*
 * Resolver.cpp
 *
 */

#include <string>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "System/Network/Resolver.hpp"

using namespace std;



namespace System
{
namespace Network
{

Resolver::Resolver(const Address &cInfo)
{
  const char *addr=cInfo.getHost().c_str();

  if( strcmp(addr, "*")==0 )        // all addresses?
    _addr.push_back( Address("0.0.0.0", cInfo.getPort() ) );    // addr-any
  else
  {
    if( inet_addr(addr)==INADDR_NONE )         // non-IP?
    {
      // if everyting fails - try DNS:
      struct hostent *dns_info=gethostbyname(addr);
      if(dns_info==NULL)                       // no match?
        throw Resolver::Exception("Resolver::Resolver(): unknown host '" +
                                  cInfo.getHost() + "'");

      // loop thorough resolved IPs
      for(unsigned int i=0; dns_info->h_addr_list[i]!=NULL; ++i)
      {
        // choose next from the list
        const in_addr *inAddr=reinterpret_cast<in_addr*>(
                                       dns_info->h_addr_list[i]);
        const char    *tab   =inet_ntoa(*inAddr);
        // add next IP to resolved base
        _addr.push_back( Address(tab, cInfo.getPort() ) );
      } // for(resolved_ips)
    }
    else // if(non-IP)
    {
      // so this is a correct (IP) address!
      _addr.push_back(cInfo);
    }
  } // else(addr=="*")
}

} // namespace Network
} // namespace System


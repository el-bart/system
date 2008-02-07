/*
 * TCPServer.mt.cpp
 *
 */
#include <iostream>
#include <stdio.h>
#include <assert.h>

#include "System/Network/TCPServer.hpp"

using namespace std;
using namespace System::Network;


int main(int argc, char **argv)
{
  // check cmd line
  if(argc!=3)
  {
    cerr<<argv[0]<<" <host> <ip>\n";
    return 1;
  }

  try
  {
    Address addr(argv[1], atoi(argv[2]));
    // connect
    cout<<argv[0]<<": openning port at "<<addr.getAddressStr()<<" ...\n";
    TCPServer s(addr);
    assert( s.isActive() );

    // process all incomming connections
    char buf[10*1024];          // nasty, but it's only mtest...
    do
    {
      cout<<argv[0]<<": listening...\n";
      cout<<argv[0]<<": (send 'quit' string to spot the server)\n";
      Connection c=s.accept();  // accept new connection

      // catch data from user
      cout<<argv[0]<<": waiting for user data...\n";
      FILE *rx=c.getRXstrm();
      fread(buf, sizeof(buf), 1, rx);
      // write out recieved data
      cout<<argv[0]<<": recieved '"<<buf<<"'\n";

      // end with this user
      cout<<argv[0]<<": closing connection...\n";
    }
    while( strcmp(buf, "quit")!=0 );
    cout<<argv[0]<<": stopping server on user request...\n";
  }
  catch(const std::exception &ex)
  {
    cerr<<argv[0]<<": std::exception: "<<ex.what()<<endl;
  }

  cout<<argv[0]<<": all done - quiting\n";
  return 0;
} // main()


/*
 * TCPClient.mt.cpp
 *
 */
#include <iostream>
#include <stdio.h>
#include <assert.h>

#include "System/Network/TCPClient.hpp"

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
    cout<<argv[0]<<": connecting to "<<addr.getAddressStr()<<" ...\n";
    TCPClient c(addr);
    assert( c.isActive() );
    cout<<argv[0]<<": connected\n";

    // write something and send it
    cout<<argv[0]<<": write message to send:\n";
    string msg;
    cin>>msg;

    // send message
    cout<<argv[0]<<": sending '"<<msg<<"' string...\n";
    FILE *tx=c.getConn()->getTXstrm();
    assert( fwrite(msg.c_str(), msg.length(), 1, tx)==1 );

    // quit
    cout<<argv[0]<<": closing connection...\n";
  }
  catch(const std::exception &ex)
  {
    cerr<<argv[0]<<": std::exception: "<<ex.what()<<endl;
  }

  cout<<argv[0]<<": all done - quiting\n";
  return 0;
} // main()


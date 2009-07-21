/*
 * Backtrace.cpp
 */
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <cassert>

#include "System/Backtrace.hpp"
//#include "System/E.hpp"

using namespace std;

namespace System
{

Backtrace::Backtrace(void)
{
  void *buffer[256];
  int   size =sizeof(buffer)/sizeof(buffer[0]);
  int   count=backtrace(buffer, size);
  // TODO: if count==size -> not whole stack trace has been read

  char **names;
  names=backtrace_symbols(buffer, count);
  if(names==NULL)
  {
    // TODO: exception
    perror("backtrace_symbols");
    exit(42);
  }

  assert( bt_.size()==0 );
  bt_.reserve(size);
  for(int i=0; i<count; ++i)
    bt_.push_back( names[i] );

  free(names);
}

std::string Backtrace::toString(void) const
{
}

} // namespace System

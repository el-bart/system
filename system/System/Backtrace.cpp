/*
 * Backtrace.cpp
 */
#include <sstream>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <cassert>

#include "System/Backtrace.hpp"
#include "System/AutoCptr.hpp"

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
    throw ExceptionSyscallFailed("Backtrace::Backtrace(): backtrace_symbols() "
                                 "failed: " + string( strerror(errno) ) );
  AutoCptr<char*> namesHolder(names);

  assert( bt_.size()==0 );
  bt_.reserve(size);
  for(int i=0; i<count; ++i)
    bt_.push_back( names[i] );
}

std::string Backtrace::toString(void) const
{
  // create single, big string with multiple lines, representing backtrace.
  stringstream ss;
  for(const_iterator it=begin(); it!=end(); ++it)
    ss<<*it<<endl;

  return ss.str();
}

} // namespace System

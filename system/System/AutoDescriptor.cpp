/*
 * AutoDescriptor.cpp
 *
 */
#include <unistd.h>

#include "System/AutoDescriptor.hpp"


namespace System
{

AutoDescriptor::AutoDescriptor(const int fd):
    _fd(fd)
{
}


AutoDescriptor::AutoDescriptor(const AutoDescriptor &ad):
  _fd(-1)
{
  passOwnership(ad);
}


AutoDescriptor::~AutoDescriptor(void)
{
  close();
}


bool AutoDescriptor::isInitialized(void) const
{
  return _fd>=0;
}


bool AutoDescriptor::operator==(const AutoDescriptor& ad) const
{
  // compare makes sense only if both fd's are initialized.
  return _fd==ad._fd && _fd!=-1;
}


void AutoDescriptor::reset(int fd)
{
  close();
  _fd=fd;
}


int AutoDescriptor::release(void)
{
  int tmp=_fd;
  _fd    =-1;
  return tmp;
}


const AutoDescriptor &AutoDescriptor::operator=(const AutoDescriptor& ad)
{
  if(&ad==this)
    return *this;
  passOwnership(ad);
  return ad;        // useless - for complience only.
}


void AutoDescriptor::passOwnership(const AutoDescriptor& ad)
{
  close();
  _fd   =ad._fd;
  ad._fd=-1;
}


void AutoDescriptor::close(void)
{
  if( isInitialized() )
  {
    ::close(_fd);
    _fd=-1;
  }
}

} // namespace System


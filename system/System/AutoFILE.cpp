/*
 * AutoFILE.cpp
 *
 */
#include <unistd.h>

#include "System/AutoFILE.hpp"


namespace System
{

AutoFILE::AutoFILE(FILE *fs):
    _fs(fs)
{
}


AutoFILE::AutoFILE(const AutoFILE &af):
  _fs(NULL)
{
  passOwnership(af);
}


AutoFILE::~AutoFILE(void)
{
  close();
}


bool AutoFILE::operator==(const AutoFILE& af) const
{
  // compare makes sense only if both fd's are initialized.
  return _fs==af._fs && _fs!=NULL;
}


void AutoFILE::reset(FILE *fs)
{
  close();
  _fs=fs;
}


FILE *AutoFILE::release(void)
{
  FILE *tmp=_fs;
  _fs      =NULL;
  return tmp;
}


const AutoFILE &AutoFILE::operator=(const AutoFILE& af)
{
  if(&af==this)
    return *this;
  passOwnership(af);
  return af;        // useless - for complience only.
}


void AutoFILE::passOwnership(const AutoFILE& ad)
{
  close();
  _fs   =ad._fs;
  ad._fs=NULL;
}


void AutoFILE::close(void)
{
  if( isInitialized() )
  {
    ::fclose(_fs);
    _fs=NULL;
  }
}

} // namespace System


/*
 * DiskFile.hpp
 *
 * representation of an opened file on disk
 * (file is beeing opened during creation).
 *
 */
#ifndef INCLUDE_SYSTEM_DISKFILE_HPP
#define INCLUDE_SYSTEM_DISKFILE_HPP

/* public header */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <assert.h>

#include "System/AutoDescriptor.hpp"
#include "System/Exception.hpp"


namespace System
{

class DiskFile: private boost::noncopyable
{
public:
  // opens/creates file on disk:
  //   fileName - name of disk fiel to be opened
  //   flags    - flags to be passed to open() call
  //   mode     - mode of file to be created
  DiskFile(const std::string &fileName,
           int    flags=O_RDWR|O_CREAT|O_LARGEFILE,
           mode_t mode =0644);

  inline const std::string &getName(void) const
  {
    return _fileName;
  }
  inline int get(void)
  {
    assert( _fd.isInitialized() );
    return _fd.get();
  }

  // removes file from fielsystem, but file is accessible
  // eitherway. it will be phisicaly remoev when will not
  // be accessed anymore.
  void unlink(void);

protected:
  // initializes DiskFile directly from given filename and
  // its descriptor - no additional checks are performed.
  // this is useful when creating unusual constructions
  // like temporary files, etc...
  DiskFile( std::pair<std::string, boost::shared_ptr<AutoDescriptor> > p );

  // throws error message for given method, making error
  // information from errno variable
  void throwFileErrorException(const char *methodName,
                               const char *action);

private:
  const std::string _fileName;
  AutoDescriptor    _fd;
}; // class DiskFile

} // namespace System

#endif


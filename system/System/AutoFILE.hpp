/*
 * AutoFILE.hpp
 *
 * class behaving like an auto_ptr<> for
 * FILE streams.
 *
 */
#ifndef INCLUDE_SYSTEM_AUTOFILE_HPP_FILE
#define INCLUDE_SYSTEM_AUTOFILE_HPP_FILE

/* public header */

#include <unistd.h>
#include <boost/operators.hpp>


namespace System
{

class AutoFILE: public boost::equality_comparable<AutoFILE>
{
public:
  explicit AutoFILE(FILE *fs=NULL);
  AutoFILE(const AutoFILE &af);
  ~AutoFILE(void);

  inline bool isInitialized(void) const
  {
    return _fs!=NULL;
  }

  inline FILE *get(void)
  {
    return _fs;
  }
  inline operator FILE*(void)
  {
    return get();
  }
  bool operator==(const AutoFILE &af) const;

  void reset(FILE *fs=NULL);
  FILE *release(void);
  const AutoFILE &operator=(const AutoFILE& af);

private:
  void passOwnership(const AutoFILE& af);
  void close(void);

  mutable FILE *_fs;
}; // class AutoFILE

} // namespace System

#endif


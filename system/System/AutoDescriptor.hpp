/*
 * AutoDescriptor.hpp
 *
 * class behaving like an auto_ptr<> for
 * file descriptors.
 *
 */
#ifndef INCLUDE_SYSTEM_AUTODESCRIPTOR_HPP_FILE
#define INCLUDE_SYSTEM_AUTODESCRIPTOR_HPP_FILE

/* public header */

#include <unistd.h>
#include <boost/operators.hpp>


namespace System
{

class AutoDescriptor: public boost::equality_comparable<AutoDescriptor>
{
public:
  explicit AutoDescriptor(const int fd=-1);
  AutoDescriptor(const AutoDescriptor &ad);
  ~AutoDescriptor(void);

  bool isInitialized(void) const;

  inline int get(void)
  {
    return _fd;
  }
  inline operator int(void)
  {
    return get();
  }
  bool operator==(const AutoDescriptor& ad) const;

  void reset(int fd=-1);
  int release(void);
  const AutoDescriptor &operator=(const AutoDescriptor& ad);

private:
  void passOwnership(const AutoDescriptor& ad);
  void close(void);

  mutable int _fd;
}; // class AutoDescriptor

} // namespace System

#endif


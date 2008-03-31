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

#include "System/AutoVariable.hpp"

namespace System
{

/** \brief helper class for internal usage in AutoDescriptor.
 */
class DescriptorHolder
{
public:
  typedef int TValue;
  /** \brief constructor setting start descriptor
   *         to be held.
   *  \param v descriptor to be held.
   */
  explicit DescriptorHolder(TValue v):
    _v(v)
  {
  }
  /** \brief default constructor. lives object undefined.
   */
  DescriptorHolder(void):
    _v(-1)
  {
  }
  /** \brief returns value of descriptor.
   *  \return descriptor being held.
   */
  inline TValue get(void) const
  {
    return _v;
  }
  /** \brief closes descriptor held inside.
   */
  void dealocate(void)
  {
    if(_v!=-1)
    {
      close(_v);
      _v=-1;
    }
  }

private:
  TValue _v;
}; // class DescriptorHolder

class AutoDescriptor: public boost::equality_comparable<AutoDescriptor>,
                      public AutoVariable<DescriptorHolder>
{
public:
  /** \brief constructor creating object to hold descriptor.
   *  \param fd file descriptor to hold inside.
   */
  explicit AutoDescriptor(const int fd=-1):
    AutoVariable<DescriptorHolder>(fd)
  {
  }
  /** \brief compares two AutoDescriptors.
   *         this is usualy used only to test for IN-equality.
   *  \return true is both objects are initialized
   *          and their descriptors are equal.
   */
  bool operator==(const AutoDescriptor& ad) const
  {
    // compare makes sense only if both fd's are initialized.
    return isInitialized() && get()==ad.get();
  }
}; // class AutoDescriptor

} // namespace System

#endif


/*
 * BadAlloc.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTIONS_BADALLOC_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTIONS_BADALLOC_HPP_FILE

/* public header */

#include "System/Exceptions/Base.hpp"

namespace System
{
namespace Exceptions
{

/** \brief internal exception class.
 */
class BadAlloc: public Base<BadAlloc, std::bad_alloc>
{
protected:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  template<typename T>
  BadAlloc(const T &msg):
    Exceptions::Base<BadAlloc, std::bad_alloc>(msg)
  {
  }
}; // class BadAlloc

} // namespace Exceptions
} // namespace System

#endif

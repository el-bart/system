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
namespace BadAlloc
{

/** \brief internal exception class.
 */
class BadAlloc: public Base<Exception, std::bad_alloc>
{
public:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  template<typename T>
  BadAlloc(const T &msg):
    Exceptions::Base<Exception, std::exception>(msg)
  {
  }
}; // class BadAlloc

} // namespace Exceptions
} // namespace System

#endif

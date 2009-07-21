/*
 * RuntimeError.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTIONS_RUNTIMEERROR_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTIONS_RUNTIMEERROR_HPP_FILE

/* public header */

#include "System/Exceptions/BaseSimple.hpp"

namespace System
{
namespace Exceptions
{

/** \brief base exception class for errors reported at runtime.
 */
class RuntimeError: public BaseSimple<RuntimeError, std::runtime_error>
{
protected:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  template<typename T>
  RuntimeError(const T &msg):
    Exceptions::BaseSimple<RuntimeError, std::runtime_error>(msg)
  {
  }
}; // class RuntimeError

} // namespace Exceptions
} // namespace System

#endif

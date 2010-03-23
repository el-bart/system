/*
 * ExceptionPointerIsNULL.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTIONPOINTERISNULL_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTIONPOINTERISNULL_HPP_FILE

/* public header */

#include "System/Exceptions/RuntimeError.hpp"

namespace System
{

/** \brief exception when NULL pointer is passed, when not expected.
 */
class ExceptionPointerIsNULL: public Exceptions::RuntimeError<ExceptionPointerIsNULL>
{
public:
  /** \brief create execption with given message.
   *  \param name name of variable that has been detected NULL.
   */
  explicit ExceptionPointerIsNULL(const char *name):
    Exceptions::RuntimeError<ExceptionPointerIsNULL>(
                         cc("NULL pointere recieved: ", name) )
  {
  }
}; // class ExceptionPointerIsNULL

} // namespace System

#endif

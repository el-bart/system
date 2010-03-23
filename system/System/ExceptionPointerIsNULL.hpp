/*
 * ExceptionPointerIsNULL.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTIONPOINTERISNULL_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTIONPOINTERISNULL_HPP_FILE

/* public header */

#include "System/Exception.hpp"

namespace System
{

/** \brief exception when NULL pointer is passed, when not expected.
 */
class ExceptionPointerIsNULL: public Exception
{
public:
  /** \brief create execption with given message.
   *  \param name name of variable that has been detected NULL.
   */
  explicit ExceptionPointerIsNULL(const char *name):
    Exception( cc("NULL pointere recieved: ", name) )
  {
  }
}; // class ExceptionPointerIsNULL

} // namespace System

#endif

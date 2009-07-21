/*
 * LogicError.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTIONS_LOGICERROR_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTIONS_LOGICERROR_HPP_FILE

/* public header */

#include "System/Exceptions/Base.hpp"

namespace System
{
namespace Exceptions
{

/** \brief base exception class for errors in program logic.
 *  \note throwing this type of error may be threated as an release-time
 *        assert equivalent.
 */
class LogicError: public Base<LogicError, std::logic_error>
{
protected:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  LogicError(const std::string &msg):
    Exceptions::Base<LogicError, std::logic_error>(msg)
  {
  }
}; // class LogicError

} // namespace Exceptions
} // namespace System

#endif

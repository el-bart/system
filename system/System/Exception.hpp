/*
 * Exception.hpp
 *
 * this is implementation class of base exception for System library and
 * should not be used as a base class outside of it.
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTION_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTION_HPP_FILE

/* public header */

#include "System/Exceptions/RuntimeError.hpp"

namespace System
{

/** \brief internal exception class.
 */
class Exception: public Exceptions::RuntimeError<Exception>
{
private:
  typedef Exceptions::RuntimeError<Exception> BaseC;

public:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  template<typename T>
  explicit Exception(const T &msg):
    BaseC(msg)
  {
    // TODO: remove this c-tor as obsolete.
  }

  /** \brief create execption with given message.
   *  \param where location of exception raising.
   *  \param msg   message to represent.
   */
  template<typename T>
  Exception(const typename BaseC::Location &where, const T &msg):
    BaseC(where, msg)
  {
  }
}; // class Exception

} // namespace System

#endif

/*
 * Exception.hpp
 *
 * everything within this namespace should use this.
 *
 */
#ifndef INCLUDE_SYSTEM_EXCEPTION_HPP_FILE
#define INCLUDE_SYSTEM_EXCEPTION_HPP_FILE

/* public header */

#include <string>
#include <exception>


namespace System
{


/** \brief internal exception class.
 */
class Exception: public std::exception
{
public:
  /** \brief create execption with given message.
   *  \param msg message to represent.
   */
  Exception(const std::string& msg):
                _msg(msg)
  {
  }
  /** \brief construct from const char*.
   *  \param msg message to represent.
   */
  Exception(const char msg[]):
                _msg(msg)
  {
  }
  /** \brief destructor requires special flags.
   */
  virtual ~Exception(void) throw()
  {
  }

  /** \brief return error message as string.
   *  \return error message.
   */
  inline const std::string& whatAsStr(void) const
  {
    return _msg;
  }
  /** \brief return error message pointer, as const char*.
   *  \return pointer to message.
   */
  virtual const char *what(void) const throw()
  {
    return _msg.c_str();
  }

private:
  std::string _msg;
}; // class Exception


}; // namespace System

#endif


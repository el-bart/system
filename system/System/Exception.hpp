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


class Exception: public std::exception
{
public:
  Exception(const std::string& msg):
                _msg(msg)
  {
  }

  Exception(const char msg[]):
                _msg(msg)
  {
  }

  virtual ~Exception(void) throw()
  {
  }

  inline const std::string& whatAsStr(void) const
  {
    return _msg;
  }

  virtual const char *what(void) const throw()
  {
    return _msg.c_str();
  }

private:
  std::string _msg;
}; // class Exception


}; // namespace System

#endif


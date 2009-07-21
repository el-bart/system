/*
 * Backtrace.hpp
 */
#ifndef INCLUDE_SYSTEM_BACKTRACE_HPP_FILE
#define INCLUDE_SYSTEM_BACKTRACE_HPP_FILE

#include <vector>
#include <string>

// TODO: tests
// TODO: comments
// TODO: implementation

namespace System
{

class Backtrace
{
private:
  typedef std::vector<std::string> BacktraceLog;
public:
  typedef BacktraceLog::const_iterator const_iterator;

  Backtrace(void);

  const_iterator begin(void) const
  {
    return bt_.begin();
  }

  const_iterator end(void) const
  {
    return bt_.end();
  }

  size_t size(void) const
  {
    return bt_.size();
  }

  std::string toString(void) const;

private:

  BacktraceLog bt_;
}; // class Backtrace

} // namespace System

#endif

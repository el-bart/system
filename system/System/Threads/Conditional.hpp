/*
 * Conditional.hpp
 *
 * class implementing functionality of pthread's
 * conditional variable.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_CONDITIONAL_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_CONDITIONAL_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>

#include "System/Threads/Mutex.hpp"
#include "System/Threads/Condition.hpp"
#include "System/Exception.hpp"


namespace System
{
namespace Threads
{

class Conditional: private boost::noncopyable
{
public:
  // test - determines if condition is met or not
  Conditional(bool test=false);

  // wait for condition to be met
  void wait(void);
  // the same as wait() but with timeout provided.
  // returns false on timeout, true upon success.
  bool wait(unsigned int uSecs);

  // signal one thread
  void signalOne(void);

  // signal all of threads
  void signalAll(void);

  // set value of condition (test) variable
  void setCondition(bool val);

private:
  bool testCondition(void);

  Mutex     _mutex;
  Condition _cond;
  bool      _test;
}; // class Conditional

} // namespace Threads
} // namespace System

#endif


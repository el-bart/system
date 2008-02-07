/*
 * ExternalLock.hpp
 *
 * critical section implementation for multiple methods
 * of one class.
 *
 * usage example:
 *
 * class MyClassToLock
 * {
 *   ...
 *   // these 3 ops should be synced together
 *   void f1(void);
 *   void f2(void);
 *   void f3(void);
 * private:
 *   friend class ExternalLock<MyClassToLock>;  // to allow mutex ops
 *   Mutex _mutex;  // name **IS** important
 * };
 *
 * ...
 * // incode usage example:
 *
 * MyClassToLock mctl;
 * ...
 * {
 *   ExternalLock<MyClassToLock> el(mctl);
 *   // now section is locked
 *   mctl.f1();
 *   mctl.f2();
 *   mctl.f3();
 * } // sesion will unlock here
 *
 *
 * ExternalLock<> reference should be passed as required
 * argument to each call requireing cynchronisation to
 * be shure that lock is present (it such a behaviour
 * is expected: AND IT SHOULD BE!).
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_EXTERNALLOCK_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_EXTERNALLOCK_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>

#include "System/Threads/Lock.hpp"


namespace System
{
namespace Threads
{

template<typename TExtLockable>
class ExternalLock: private boost::noncopyable
{
public:
  inline ExternalLock(TExtLockable &l):
    _lock(l._mutex)
  {
  }
  // this is useful sometimes, if EL isn't needed itself,
  // and compiler gives warrnings about unused
  // argument/variable. this inlines to empty code.
  inline void doNothing(void) const
  {
  }
private:
  Lock _lock;
}; // class ExternalLock

} // namespace Threads
} // namespace System

#endif


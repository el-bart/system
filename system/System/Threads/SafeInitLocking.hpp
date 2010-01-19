/*
 * SafeInitLocking.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_SAFEINITLOCKING_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_SAFEINITLOCKING_HPP_FILE

/* public header */

#include <pthread.h>
#include <boost/noncopyable.hpp>

namespace System
{
namespace Threads
{

/** \brief lock that allows thread-safe locking during initialization.
 *
 *  problem with common C++ wrappers is that they require c-tor to be run
 *  before being used. this is problematic, when using global objects from
 *  multiple threads, before main() since there is no guarantee that locks
 *  are aldready initialized.
 *
 *  the same goes for global resources that are not guaranteed to be
 *  initialized before being used (i.e. before entering main and after
 *  leaving main).
 *
 *  <code>
 *  // MyClass.cpp file
 *
 *  SYSTEM_MAKE_SAFEINIT_MUTEX(g_myMutex)   // mutex in initialized in
 *                                          // compile-time. notice NO ending
 *                                          // semicollon in macro usage.
 *
 *  void MyClass::staticMethodUsedBeforeMain(void)
 *  {
 *    SafeInitLock lock(g_myMutex);         // we can lock, since mutex is
 *                                          // always valid
 *    // [critical section goes here]
 *  }
 *  </code>
 */
class SafeInitLock: private boost::noncopyable
{
public:
  /** \brief typedef to use for representation of mutex. */
  typedef pthread_mutex_t MutexType;

  /** \brief lock safely initialized mutex.
   *  \param mutex mutex to be locked.
   */
  explicit SafeInitLock(pthread_mutex_t &mutex);
  /** \brief unlock mutex.
   */
  ~SafeInitLock(void);

private:
  MutexType &mutex_;
}; // class SafeInitLock


/** \brief creates mutex type, that will be initialized during compile-time.
 *  \param name name for this mutex.
 *  \note when using this macro do NOT end it with a semicollon.
 *  \warning this macro MUST be places IN CPP file!
 */
#define SYSTEM_MAKE_SAFEINIT_MUTEX(name) namespace { ::System::Threads::SafeInitLock::MutexType name=PTHREAD_MUTEX_INITIALIZER; }

} // namespace Threads
} // namespace System

#endif

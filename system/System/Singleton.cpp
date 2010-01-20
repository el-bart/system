/*
 * Singleton.cpp
 *
 */
#include "System/Singleton.hpp"

namespace System
{
namespace detail
{

SYSTEM_MAKE_STATIC_SAFEINIT_MUTEX(g_mutex);

Threads::SafeInitLock::MutexType &getSingletonMutex(void)
{
  return g_mutex;
}

} // namespace detail
} // namespace System

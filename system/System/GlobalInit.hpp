/*
 * GlobalInit.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_GLOBALINIT_HPP_FILE
#define INCLUDE_SYSTEM_GLOBALINIT_HPP_FILE

/* public header */

#include "System/Threads/SafeInitLocking.hpp"
#include "System/AtExit.hpp"

// TODO: check this code
// TODO: write tests


namespace System
{

namespace detail
{
/** \brief helper function giving access to global mutex.
 *  \return reference to global mutex used for locking GlobalInit() internals.
 */
Threads::SafeInitLock::MutexType &getGlabalInitMutex(void);
} // namespace detail

/**
 * \brief template wrapper for global (de)initilization oof data.
 *
 * number of libraries uses global data that are not initialized
 * in the proper way, sometimes are not deinitializaed at all, initalizaiton
 * is not thread safe, etc... this wrapper solves this issues.
 *
 * this class initializes user object in thread-safe way, and deinitializes
 * it uppon program exit. when it is needed once more, it will be
 * re-initialized and deallocated stright away.
 *
 * used-defined T type has to provide static methods init() and deinit()
 * that performs as-is initialization (i.e. no locking, checks, etc...)
 * and deinitialization of given element, respecitively.
 * NOTE: deinit() must NOT throw!
 */
template<typename T>
class GlobalInit
{
public:
  GlobalInit(void)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    if( counter(lock)==0 )
    {
      AtExit::TDeallocPtr  deinit(new GlobalDeinit);
      GlobalDeinit        *tmp=deinit.get();
      AtExit::registerDeallocator(deinit);
      T::init();                            // initialize user object
      tmp->unlock();                        // allow deallocation in atexit()
      atExitMark(lock)=false;
    }
    // mark usage
    ++counter(lock);
  }

  GlobalInit(const GlobalInit &/*other*/)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    assert( counter(lock)>0 );
    // mark usage
    ++counter(lock);
  }

  const GlobalInit &operator=(const GlobalInit &other)
  {
    if(this==&other)
      return *this;
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    assert( counter(lock)>0 );
    // mark usage
    ++counter(lock);
  }

  ~GlobalInit(void)
  {
    Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
    assert( counter(lock)>0 );
    // mark usage
    --counter(lock);
    // if this is the last instance and atexit() has been already
    // finished we have to deallocate ourselves
    if( counter(lock)==0 && atExitMark(lock)==true )
    {
      T::deinit();
      atExitMark(lock)=false;
    }
  }

private:
  // helper class to deinitialize given library
  class GlobalDeinit: public AtExitResourceDeallocator
  {
  public:
    GlobalDeinit(void):
      unlocked_(false)
    {
    }
    // enable deallocation feature
    void unlock(void)
    {
      Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
      unlocked_=true;
    }
    // deallocation itself
    virtual void deallocate(void)
    {
      Threads::SafeInitLock lock( detail::getGlabalInitMutex() );
      if(unlocked_==false)      // something failed during initialization - do nothing
        return;
      if( counter(lock)==0 )    // only if noone is using this any more
        T::deinit();
      atExitMark(lock)=true;    // mark that atexit() has been already done
    }

  private:
    bool unlocked_;
  }; // class GlobalDeinit

  // this must be done within a lock to ensure safe initialization
  unsigned long &counter(Threads::SafeInitLock &)
  {
    static unsigned long cnt=0;
    return cnt;
  }
  // mark that atexit handle has already finished
  bool &atExitMark(Threads::SafeInitLock &)
  {
    static bool mark=false;
    return mark;
  }
}; // class GlobalInit

} // namespace System

#endif

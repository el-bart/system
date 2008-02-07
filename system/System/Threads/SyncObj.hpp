/*
 * SyncObj.hpp
 *
 * generic implementation of synchronized object.
 * access to object created inside is sure to be thread safe.
 *
 * code example:
 *
 *
 *   struct MyObj
 *   {
 *     void doSth(void)
 *     {
 *       // ...
 *     }
 *   };
 *
 *   class MySyncObj: public SyncObj<MyObj>
 *   {
 *   public:
 *     MySyncObj(void)
 *     {
 *       // initialize SyncObj base class
 *       init(&_mo);
 *     }
 *   private:
 *     MyObj _mo;
 *   };
 *
 *
 * then it can be used as follows:
 *
 *   MySyncObj          mso;
 *   { // begin critical section block
 *     MySyncObj::ExtLock el(mso);
 *     mso(el)->doSth();
 *   } // end of critical section
 *
 *
 * please notice that SyncObj<> itself is NOT
 * copyable.
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_SYNCOBJ_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_SYNCOBJ_HPP_FILE

/* public header */

#include <cassert>

#include "System/Threads/ExternalLock.hpp"


namespace System
{
namespace Threads
{

template<typename T>
class SyncObj
{
public:
  typedef T                   TData;
  typedef SyncObj<T>          TThis;
  typedef ExternalLock<TThis> ExtLock;

  // return externaly synchronized object
  inline TData *operator()(const ExtLock &el)
  {
    el.doNothing();
    assert(_ptr!=NULL);
    return _ptr;
  }
  inline const TData *operator()(const ExtLock &el) const
  {
    el.doNothing();
    assert(_ptr!=NULL);
    return _ptr;
  }

protected:
  inline SyncObj(void):
    _ptr(NULL)
  {
  }
  // init object within derived's constructor, since
  // it is not possible to init it before base.
  inline void init(TData *ptr)
  {
    _ptr=ptr;
    assert(_ptr!=NULL);
  }

private:
  friend class ExternalLock<TThis>;  // to allow mutex ops

  TData *_ptr;          // external pointer to user data
  Mutex  _mutex;        // for ExternalLock
}; // class SyncObj

} // namespace Threads
} // namespace System

#endif


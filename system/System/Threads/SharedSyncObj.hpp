/*
 * SharedSyncObj.hpp
 *
 * generic implementation of synchronized object that
 * can be shared between threads.
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
 *   class MySharedSyncObj: SharedSyncObj<MySyncObj>
 *   {
 *   public:
 *     MySharedSyncObj(void):
 *       SharedSyncObj<MySyncObj>( new MyObj )
 *     {
 *     }
 *   };
 *
 *
 * then it can be used as follows:
 *
 *   MySharedSyncObj            msso;
 *   { // begin critical section block
 *     MySharedSyncObj::ExtLock el(mso);
 *     msso(el)->doSth();
 *   } // end of critical section
 *
 */
#ifndef INCLUDE_SYSTEM_THREADS_SHAREDSYNCOBJ_HPP_FILE
#define INCLUDE_SYSTEM_THREADS_SHAREDSYNCOBJ_HPP_FILE

/* public header */

#include <boost/shared_ptr.hpp>
#include <cassert>

#include "System/Threads/SyncObj.hpp"


namespace System
{
namespace Threads
{

template<typename TSyncObj>
class SharedSyncObj
{
public:
  typedef typename TSyncObj::ExtLock ExtLock;
  typedef typename TSyncObj::TData   TData;

  // return externaly synchronized object
  inline TData *operator()(const ExtLock &el)
  {
    el.doNothing();
    assert(_so.get()!=NULL);
    return (*_so.get())(el);
  }
  inline const TData *operator()(const ExtLock &el) const
  {
    el.doNothing();
    assert(_so.get()!=NULL);
    return (*_so.get())(el);
  }

  // this convertion operator is required to allow
  // ExternalLock on internal class
  inline operator TSyncObj&(void)
  {
    return *_so.get();
  }

protected:
  explicit SharedSyncObj(TSyncObj *newSyncObj):
    _so(newSyncObj)
  {
  }

private:
  boost::shared_ptr<TSyncObj> _so;
}; // class SyncObj

} // namespace Threads
} // namespace System

#endif


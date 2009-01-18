/*
 * AtExitImpl.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ATEXITIMPL_HPP_FILE
#define INCLUDE_SYSTEM_ATEXITIMPL_HPP_FILE

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "System/AtExitResourceDeallocator.hpp"
#include "System/AtExit.hpp"


namespace System
{

/** \brief implementation class of AtExit.
 *  \note since AtExit is thread-safe, this one is not.
 */
class AtExitImpl: private boost::noncopyable
{
public:
  /** \brief create object.
   */
  AtExitImpl(void);
  /** \brief destroy object and ensure deallocateAll() has been called.
   */
  ~AtExitImpl(void);
  /** \brief deallocates all registered resources.
   *  \note this method shoul dbe called exactly once during lifetime
   *        of created object. no regsters can be done after this method
   *        has been called.
   */
  void deallocateAll(void);
  /** \brief registers new deallocator.
   *  \param ptr deallocator to be registered.
   */
  void registerDeallocator(AtExit::TDeallocPtr ptr);

private:
  typedef boost::shared_ptr<AtExitResourceDeallocator> TElem;
  typedef std::list<TElem>                             TList;

  TList deallocators_;
  bool  deallocationDone_;
}; // class AtExitImpl

} // namespace System

#endif

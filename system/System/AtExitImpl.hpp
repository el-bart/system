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

class AtExitImpl: private boost::noncopyable
{
public:
  AtExitImpl(void);
  ~AtExitImpl(void);
  void deallocateAll(void);
  void registerDeallocator(AtExit::TDeallocPtr ptr);

private:
  typedef boost::shared_ptr<AtExitResourceDeallocator> TElem;
  typedef std::list<TElem>                             TList;

  TList deallocators_;
  bool  deallocationDone_;
}; // class AtExitImpl

} // namespace System

#endif

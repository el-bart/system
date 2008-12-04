/*
 * AtExitImpl.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ATEXITIMPL_HPP_FILE
#define INCLUDE_SYSTEM_ATEXITIMPL_HPP_FILE

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "System/AtExitResourceDealocator.hpp"
#include "System/AtExit.hpp"


namespace System
{

class AtExitImpl: private boost::noncopyable
{
public:
  AtExitImpl(void);
  ~AtExitImpl(void);
  void dealocateAll(void);
  void registerDealocator(AtExit::Tptr ptr);

private:
  typedef boost::shared_ptr<AtExitResourceDealocator> TElem;
  typedef std::list<TElem>                            TList;

  TList dealocators_;
  bool  dealocationDone_;
}; // class AtExitImpl

} // namespace System

#endif

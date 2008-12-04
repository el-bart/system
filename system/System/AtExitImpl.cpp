/*
 * AtExitImpl.cpp
 *
 */
#include <iostream>
#include <cassert>
#include <stdlib.h>

#include "System/AtExitImpl.hpp"

using namespace std;


namespace System
{

AtExitImpl::AtExitImpl(void):
  dealocationDone_(false)
{
}

AtExitImpl::~AtExitImpl(void)
{
  assert(dealocationDone_ && "dealocateAll() has not been called. "
                             "this suggest resource leak.");
}

void AtExitImpl::dealocateAll(void)
{
  assert(!dealocationDone_ && "dealocateAll() called more than once");
  dealocationDone_=true;

  // loop throught elements
  for(TList::reverse_iterator it=dealocators_.rbegin();
      it!=dealocators_.rend();
      ++it)
  {
    try
    {
      // free one more resource :)
      (*it)->dealocate();
    }
    catch(...)
    {
      assert(!"fatal error - exception from "
              "AtExitResourceDealocator::dealocate() has been thrown");
      cerr<<"fatal error - exception from "
            "AtExitResourceDealocator::dealocate() has been thrown\n";
      abort();
    }
  }
  // ensure each dealocation will take place just once
  dealocators_.clear();
}

void AtExitImpl::registerDealocator(AtExit::Tptr ptr)
{
  assert(!dealocationDone_ && "dealocateAll() already called");

  TElem elem( ptr.release() );  // convert to container-safe ptr type
  dealocators_.push_back(elem); // add to container
}

} // namespace System

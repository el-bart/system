/*
 * AtExit.cpp
 *
 */
#include <stdlib.h>     // atexit()
#include <cassert>

#include "System/AtExit.hpp"
#include "System/AtExitImpl.hpp"

using namespace std;


namespace
{
// pointer to implementation class of AtExit. it is static, raw
// pointer since it will be freed by AtExit() uppon application
// termination.
// by default this pointer will be NULL when application starts.
// destination object will be assigned uppon first AtExit class
// usage (it registeres this pointer).
System::AtExitImpl *atExitImpl;
} // unnamed namespace


// helper that will dealocate objects inside queue.
extern "C"
{
static void cStyleCallForAtExit(void)
{
  if(atExitImpl!=NULL)
  {
    atExitImpl->dealocateAll();
    atExitImpl=NULL;    // dealocation already took place in AtExitImpl
  }
} // cStyleCallForAtExit()
} // extern "C"


namespace System
{

// helper namespace for self-dealocator
namespace
{
class AtExitImplDealocator: public AtExitResourceDealocator
{
public:
  AtExitImplDealocator(auto_ptr<AtExitImpl> pimpl):
    pimpl_(pimpl)
  {
    assert( pimpl_.get()!=NULL );
  }

  virtual void dealocate(void)
  {
    pimpl_.reset(NULL);
  }

private:
  auto_ptr<AtExitImpl> pimpl_;
}; // class AtExitImplDealocator
} // unnamed namespace



void AtExit::registerDealocator(Tptr p)
{
  static AtExit instance;
  instance.registerInternal(p);
}

AtExit::AtExit(void)
{
  assert(atExitImpl==NULL);

  if( atexit(cStyleCallForAtExit)!=0 )
    throw Exception("AtExit::AtExit(): "
                    "unable to register handler in atexit() syscall");

  try
  {
    // create implementation
    auto_ptr<AtExitImpl>  ptr( new AtExitImpl );
    AtExitImpl           *tmp=ptr.get();
    Tptr                  pimplDealoc( new AtExitImplDealocator(ptr) );

    // init global pointer
    atExitImpl=tmp;
    // add self clean-up
    assert(atExitImpl!=NULL);
    registerInternal(pimplDealoc);
  }
  catch(...)
  {
    // this looks a bit creepy, but it's a safety precautions
    // in case when self-registration would fail.
    atExitImpl=NULL;
    throw;
  }
  assert(atExitImpl!=NULL);
}

void AtExit::registerInternal(Tptr p)
{
  assert(atExitImpl!=NULL);
  if( p.get()==NULL )
    throw Exception("AtExit::registerInternal(): "
                    "NULL pointer recieved for registration");

  atExitImpl->registerDealocator(p);
}

} // namespace System

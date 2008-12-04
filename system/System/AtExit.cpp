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
//
// pointer to implementation class of AtExit. it is static, raw
// pointer since it will be freed by AtExit() uppon application
// termination.
// by default this pointer will be NULL when application starts.
// destination object will be assigned uppon first AtExit class
// usage (it registeres this pointer).
//
System::AtExitImpl *atExitImpl;
} // unnamed namespace


// helper that will deallocate objects inside queue.
extern "C"
{
static void cStyleCallForAtExit(void)
{
  if(atExitImpl!=NULL)
  {
    // run dealocation of registered elements
    atExitImpl->deallocateAll();
    // free resource
    delete atExitImpl;
    atExitImpl=NULL;
  }
  assert(atExitImpl==NULL);
} // cStyleCallForAtExit()
} // extern "C"


namespace System
{

void AtExit::registerDeallocator(TDeallocPtr p)
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

  // init global pointer
  atExitImpl=new AtExitImpl;
  // sanity check
  assert(atExitImpl!=NULL);
}

void AtExit::registerInternal(TDeallocPtr p)
{
  assert(atExitImpl!=NULL);
  if( p.get()==NULL )
    throw Exception("AtExit::registerInternal(): "
                    "NULL pointer recieved for registration");

  atExitImpl->registerDeallocator(p);
}

} // namespace System

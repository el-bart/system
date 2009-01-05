/*
 * AtExit.cpp
 *
 */
#include <stdlib.h>     // atexit()
#include <boost/checked_delete.hpp>
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
    // do a safe-pass to remove pointer
    System::AtExitImpl *tmpPtr=atExitImpl;
    atExitImpl=NULL;

    // run dealocation of registered elements
    tmpPtr->deallocateAll();
    // free resource
    boost::checked_delete(tmpPtr);
  }
  assert(atExitImpl==NULL);
} // cStyleCallForAtExit()
} // extern "C"


namespace System
{

void AtExit::registerDeallocator(TDeallocPtr p)
{
  static bool init=AtExit::init();  // initialize all globals
  assert(init==true);               // check just in case...
  AtExit::registerInternal(p);      // forward call to implementation
}

bool AtExit::init(void)
{
  assert(atExitImpl==NULL);

  // this call, if there is a problem, can be registered/called
  // multiple times...
  if( atexit(cStyleCallForAtExit)!=0 )
    throw Exception("AtExit::AtExit(): "
                    "unable to register handler in atexit() syscall");

  // sanity check
  assert(atExitImpl==NULL);

  // init global pointer
  atExitImpl=new AtExitImpl;

  // sanity check
  assert(atExitImpl!=NULL);
  return true;
}

void AtExit::registerInternal(TDeallocPtr p)
{
  if( p.get()==NULL )
    throw Exception("AtExit::registerInternal(): "
                    "NULL pointer recieved for registration");

  assert(atExitImpl!=NULL);
  atExitImpl->registerDeallocator(p);
}

} // namespace System

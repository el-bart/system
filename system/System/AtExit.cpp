/*
 * AtExit.cpp
 *
 */
#include <iostream>
#include <stdlib.h>     // atexit()
#include <pthread.h>
#include <boost/checked_delete.hpp>
#include <cassert>

#include "System/AtExit.hpp"
#include "System/AtExitImpl.hpp"
#include "System/Threads/SafeInitLocking.hpp"

using namespace std;
using System::Threads::SafeInitLock;


namespace
{

//
// pointer to implementation class of AtExit. it is static, raw
// pointer since it will be freed by AtExit() uppon application
// termination.
//
// by default this pointer will be NULL when application starts.
// destination object will be assigned uppon first AtExit class
// usage (it registeres this pointer).
//
// compile-time initialized mutex ensures whole construction is
// thread safe from the very begining (before any static constructors
// are run), to the very end.
//
System::AtExitImpl *atExitImpl=NULL;
SYSTEM_MAKE_SAFEINIT_MUTEX(mutex)

} // unnamed namespace


// helper that will deallocate objects inside queue and AtExitImpl
// class itself.
extern "C"
{
static void cStyleCallForAtExit(void)
{
  SafeInitLock lock(mutex);
  // pointer can be null in case when this function has been already
  // registered, but AtExitImpl's constructor thrown exception.
  if(atExitImpl!=NULL)
  {
    // run dealocation of registered elements
    atExitImpl->deallocateAll();
    // free resource
    boost::checked_delete(atExitImpl);
    atExitImpl=NULL;
  }
  assert(atExitImpl==NULL);
} // cStyleCallForAtExit()
} // extern "C"


namespace System
{

void AtExit::registerDeallocator(TDeallocPtr p)
{
  SafeInitLock lock(mutex);
  if(atExitImpl==NULL)          // not initialized?
    AtExit::init();             // will throw on failure
  assert(atExitImpl!=NULL);

  AtExit::registerInternal(p);  // forward call to implementation
}

void AtExit::init(void)
{
  // lock for this call is made in registerDeallocator()
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
}

void AtExit::registerInternal(TDeallocPtr p)
{
  // lock for this call is made in registerDeallocator()
  if( p.get()==NULL )
    throw Exception("AtExit::registerInternal(): "
                    "NULL pointer recieved for registration");

  assert(atExitImpl!=NULL);
  atExitImpl->registerDeallocator(p);
}

} // namespace System

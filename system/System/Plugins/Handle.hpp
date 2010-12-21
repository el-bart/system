/*
 * Handle.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_PLUGINS_HANDLE_HPP_FILE
#define INCLUDE_SYSTEM_PLUGINS_HANDLE_HPP_FILE

/* public header */

#include <boost/noncopyable.hpp>
#include <dlfcn.h>
#include <cassert>

#include "System/ExceptionPointerIsNULL.hpp"
#include "System/Plugins/ExceptionCannotReadSymbol.hpp"

namespace System
{
namespace Plugins
{

/** \brief helper object owning handle returned by dlopen().
 */
class Handle: private boost::noncopyable
{
public:
  /** \brief create proxy-object.
   *  \param h handle to take (cannot be NULL).
   *  \note object takes ownership of 'h'.
   */
  explicit Handle(void *h):
    h_(h)
  {
    if(h_==NULL)
      throw ExceptionPointerIsNULL(SYSTEM_SAVE_LOCATION, "h");
  }
  /** \brief deallocate handle.
   */
  ~Handle(void)
  {
    dlclose( get() );
  }

  /** \brief gets given symbol from handle.
   *  \param name name of the symbol to get.
   *  \return symbol with a given name.
   *
   *  call throws an error if symbol gy a given name does not exist.
   *
   *  \warning since this is C++ interface to C calls types are NOT checked
   *           thus user must ensure that symbol with a given name really has
   *           supplied signature - otherwise undefined behavior may occure.
   */
  template<typename T>
  T getSymbol(const std::string &name)
  {
    dlerror();  // clean previous error message
    T t;
    // NOTE: this is a hack, since in C99 casting from void* to function
    //       pointer is an undefined behavior.
    *(void**)(&t)=dlsym( get(), name.c_str() );
    const char *err=dlerror();
    if(err!=NULL)
      throw ExceptionCannotReadSymbol(SYSTEM_SAVE_LOCATION, name, err);
    return t;
  }

private:
  void *get(void)
  {
    assert(h_!=NULL);
    return h_;
  }

  void *h_;
}; // class Handle

} // namespace Plugins
} // namespace System

#endif

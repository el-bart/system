/*
 * Builder.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_PLUGINS_BUILDER_HPP_FILE
#define INCLUDE_SYSTEM_PLUGINS_BUILDER_HPP_FILE

/* public header */

#include <boost/filesystem.hpp>

#include "System/SharedPtrNotNULL.hpp"
#include "System/Plugins/Handle.hpp"
#include "System/Plugins/ExceptionCannotOpenSharedObject.hpp"

namespace System
{
namespace Plugins
{

/** \brief builder of handles.
 */
class Builder
{
public:
  /** \brief non-NULL pointer to Handle. */
  typedef SharedPtrNotNULL<Handle> PtrNN;

  explicit Builder(bool makeSymbolsVisible=false, bool lazyResolving=true);

  PtrNN open(const boost::filesystem::path &so) const;

private:
  int flags_;
}; // class Builder

} // namespace Plugins
} // namespace System

#endif

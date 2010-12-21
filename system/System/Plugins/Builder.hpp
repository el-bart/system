/*
 * Builder.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_PLUGINS_BUILDER_HPP_FILE
#define INCLUDE_SYSTEM_PLUGINS_BUILDER_HPP_FILE

/* public header */

#include <boost/filesystem.hpp>

#include "System/Plugins/DynamicObject.hpp"
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
  explicit Builder(bool makeSymbolsVisible=false, bool lazyResolving=true);

  DynamicObject open(const boost::filesystem::path &so) const;

private:
  int flags_;
}; // class Builder

} // namespace Plugins
} // namespace System

#endif

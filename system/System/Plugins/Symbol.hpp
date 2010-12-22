/*
 * Symbol.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_PLUGINS_SYMBOL_HPP_FILE
#define INCLUDE_SYSTEM_PLUGINS_SYMBOL_HPP_FILE

/* public header */

#include <string>

#include "System/Plugins/Handle.hpp"

namespace System
{
namespace Plugins
{

template<typename S>
class Symbol
{
public:
  Symbol(HandlePtrNN h, const std::string &name, S s):
    h_(h),
    name_(name),
    s_(s)
  {
  }

  const std::string &name(void)
  {
    return name_;
  }
  S get(void)
  {
    return s_;
  }
  S get(void) const
  {
    return s_;
  }

private:
  HandlePtrNN h_;
  std::string name_;
  S           s_;
}; // class Symbol

} // namespace Plugins
} // namespace System

#endif

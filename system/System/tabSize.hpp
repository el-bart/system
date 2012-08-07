#ifndef INCLUDE_SYSTEM_TABSIZE_HPP_FILE
#define INCLUDE_SYSTEM_TABSIZE_HPP_FILE

namespace System
{

template<typename T, size_t N>
size_t tabSize(const T (&)[N])
{
  return N;
} // tabSize()

} // namespace System

#endif

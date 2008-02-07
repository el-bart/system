/*
 * keepRange.hpp
 *
 * function ensuring that result fits specified range
 * of acceptable values.
 *
 */
#ifndef INCLUDE_SYSTEM_KEEPRANGE_HPP_FILE
#define INCLUDE_SYSTEM_KEEPRANGE_HPP_FILE

/* public header */

#include <algorithm>


namespace System
{

template<typename T>
inline T keepRange(const T in, const T min, const T max)
{
  return std::min( max, std::max(min, in) );
}

} // namespace System

#endif


/*
 * keepRange.hpp
 *
 * set of functions ensuring given variable
 * fits specified range.
 *
 */
#ifndef INCLUDE_SYSTEM_KEEPRANGE_HPP_FILE
#define INCLUDE_SYSTEM_KEEPRANGE_HPP_FILE

/* public header */

#include <algorithm>
#include <boost/limits.hpp>

#include "System/Exception.hpp"

namespace System
{

// returns value that fits in given range.
template<typename T>
inline T keepRange(const T in, const T min, const T max)
{
  if( min>max )
    throw System::Exception("System::keepRange(): "
                            "incorrect values - min>max");
  return std::min( max, std::max(min, in) );
}

// returns converted value, that fits in
// destination's type value range.
template<typename Tout, typename Tin>
inline Tout keepRange(const Tin v)
{
  static const Tout min=std::numeric_limits<Tout>::min();
  static const Tout max=std::numeric_limits<Tout>::max();
  if(v<min)
    return min;
  if(v>max)
    return max;
  return v;
}

} // namespace System

#endif


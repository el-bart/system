/*
 * Average.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_MATH_AVERAGE_HPP
#define INCLUDE_SYSTEM_MATH_AVERAGE_HPP

#include <cmath>
#include <cassert>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>

#include "System/Math/arraySumFastFP.hpp"

namespace System
{
namespace Math
{

template<typename FP, typename TConstIter, FP (*sumFP)(TConstIter, TConstIter)>
class Average
{
public:
  Average(const TConstIter begin, const TConstIter end):
    count_(0u),
    avg_(0.0),
    stdDev_(0.0)
  {
    // count number of elements
    for(TConstIter it=begin; it!=end; ++it)
      ++count_;

    // compute the average
    avg_=(*sumFP)(begin, end)/count_;

    // compute standard deviation
    if(count_==1u)
    {
      stdDev_=0;
      return;
    }
    assert(count_>1);
    // TODO: work in progress
  }

  size_t count(void) const
  {
    return count_;
  }
  FP avg(void) const
  {
    return avg_;
  }
  FP stdDev(void) const
  {
    return stdDev_;
  }

private:
  BOOST_STATIC_ASSERT( boost::is_floating_point<FP>::value );

  size_t count_;
  FP     avg_;
  FP     stdDev_;
}; // class Average

} // namespace Math
} // namespace System

#endif

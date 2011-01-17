/*
 * arraySumPrecFP.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_MATH_ARRAYSUMPRECFP_HPP_FILE
#define INCLUDE_SYSTEM_MATH_ARRAYSUMPRECFP_HPP_FILE

/* public header */

#include <algorithm>
#include <iterator>
#include <vector>
#include <cassert>

#include "System/Math/arraySumFastFP.hpp"

namespace System
{
namespace Math
{

/** \brief very precise floating point computation.
 *
 *  this algorithm is more precise variant of arraySumFastFP(). though
 *  it has O(ln(N)*N) comutational complexity and O(N) memory usage.
 */
template<typename TElem, typename TConstIter>
TElem arraySumPrecFP(const TConstIter begin, const TConstIter end)
{
  size_t count=0;
  for(TConstIter it=begin; it!=end; ++it)
    ++count;

  typedef std::vector<TElem> TmpCont;
  TmpCont tmp;
  tmp.reserve(count);
  std::copy(begin, end, std::insert_iterator<TmpCont>(tmp, tmp.begin()) );
  assert( tmp.size()==count );

  return arraySumFastFP<TElem>( tmp.begin(), tmp.end() );
} // arraySumPrecFP()

} // namespace Math
} // namespace System

#endif

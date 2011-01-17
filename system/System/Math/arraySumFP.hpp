/*
 * arraySumFP.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_MATH_ARRAYSUMFP_HPP_FILE
#define INCLUDE_SYSTEM_MATH_ARRAYSUMFP_HPP_FILE

/* public header */

#include "System/Math/ExceptionInvalidRange.hpp"

namespace System
{
namespace Math
{

/** \brief sum given range of elements.
 *  \param begin const iterator to the begining of the collection.
 *  \param end   const iterator to the end of the collection.
 *
 *  this call uses special algorithm for summing to minimize FP error.
 */
template<typename TElem, typename TConstIter>
TElem arraySumFP(const TConstIter begin, const TConstIter end)
{
  if(begin==end)
    throw ExceptionInvalidRange(SYSTEM_SAVE_LOCATION, "iterator range is empty");

  TConstIter it       =begin;
  TElem      sum      =*it;
  TElem      smallBits=0;

  for(++it; it!=end; ++it)
  {
    const TElem y  =*it+smallBits;
    const TElem tmp=sum+y;
    smallBits=y-(tmp-sum);
    sum      =tmp;
  }

  return sum;
} // arraySumFP()

} // namespace Math
} // namespace System

#endif

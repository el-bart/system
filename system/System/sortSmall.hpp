/*
 * sortSmall.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_SORTSMALL_HPP_FILE
#define INCLUDE_SYSTEM_SORTSMALL_HPP_FILE

/* public header */

namespace System
{

namespace detail
{
struct DefaultSWO
{
  template<typename T>
  bool operator()(const T &left, const T &right) const
  {
    return left<right;
  }
}; // struct DefaultSWO

template<typename T>
inline void swapElements(T &e1, T &e2)
{
  const T tmp=e1;
  e1=e2;
  e2=tmp;
}
} // namespace detail



template<typename TIterator, typename TStrictWeakOrdering>
void sortSmall(TIterator begin, TIterator end, TStrictWeakOrdering swo)
{
  if(begin==end)                // empty array is always sorted.
    return;

  TIterator loop=begin;
  ++loop;
  for(; loop!=end; ++loop)      // N-1 loops
  {
    bool changed=false;

    TIterator itCurr=begin;
    TIterator itNext=begin;
    ++itNext;
    for(; itNext!=end; ++itCurr, ++itNext)
      if( swo(*itNext, *itCurr) )
      {
        detail::swapElements(*itNext, *itCurr);
        changed=true;
      }

    // no more repeats if already sorted
    if(!changed)
      break;
  }
}

template<typename TIterator>
void sortSmall(TIterator begin, TIterator end)
{
  sortSmall(begin, end, detail::DefaultSWO() );
}

} // namespace System

#endif

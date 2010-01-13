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
/** \brief default strict-weak-ordering functor.
 */
struct DefaultSWO
{
  /** \brief less-then operator equivalent.
   *  \param left  left argument for '<' opertaion.
   *  \param right right argument for '<' opertaion.
   */
  template<typename T>
  bool operator()(const T &left, const T &right) const
  {
    return left<right;
  }
}; // struct DefaultSWO

/** \brief helper funciton swapping two elements.
 *  \param e1 element to swap.
 *  \param e2 element to swap with.
 */
template<typename T>
inline void swapElements(T &e1, T &e2)
{
  const T tmp=e1;
  e1=e2;
  e2=tmp;
}
} // namespace detail


/** \brief small containers sorter.
 *  \param begin iterator where sort should start.
 *  \param end   iterator indicating end of sorted elements.
 *  \param swo   strict-weak-ordering operator to be used.
 *  \note sorting is stable.
 *  \note iterators are required to be forward-iterators (but not required
 *        to be random-access iterators).
 *
 *  implementation of std::sort<>() algorithm but dedicated to small and
 *  very small data sets. usually algorithms that have good complexity
 *  like O(n*ln(n)) does not behave well on small data sets. when
 *  collection/array to be sorder is small it takes too much time to prepare
 *  initial strucutres comparing to acctual sorting. so if we expect that
 *  data set is small (few, few tens elements) it is beneficial to use simpler
 *  algorithms that will sort data faster.
 *
 *  another advantage of simple algorithm provided here is using only forward
 *  iterators, so one can sort not only vectors/arrays but lists as well.
 *
 *  current implementation uses improved bubble sort, but it may change in the
 *  future to some other, fast-on-small-data sorting algorithm.
 */
template<typename TIterator, typename TStrictWeakOrdering>
void sortSmall(TIterator begin, TIterator end, TStrictWeakOrdering swo)
{
  if(begin==end)                // empty array is always sorted.
    return;

  bool changed;
  do
  {
    changed=false;
    TIterator itCurr=begin;
    TIterator itNext=begin;
    ++itNext;
    for(; itNext!=end; ++itCurr, ++itNext)
      if( swo(*itNext, *itCurr) )
      {
        detail::swapElements(*itNext, *itCurr);
        changed=true;
      }
  }
  while(changed);
}


/** \brief small containers sorter.
 *  \param begin iterator where sort should start.
 *  \param end   iterator indicating end of sorted elements.
 *  \note sorting is stable.
 *  \note iterators are required to be forward-iterators (but not required
 *        to be random-access iterators).
 *
 *  sorting algorithm version using default strict-weak-ordering operator.
 */
template<typename TIterator>
void sortSmall(TIterator begin, TIterator end)
{
  sortSmall(begin, end, detail::DefaultSWO() );
}

} // namespace System

#endif

/*
 * Comparer.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_DETAIL_COMPARER_HPP_FILE
#define INCLUDE_SYSTEM_DETAIL_COMPARER_HPP_FILE

/* public header */

#include <cstring>
#include <cassert>

namespace System
{
namespace detail
{

/** \brief helper comparing given elements.
 */
template<typename T>
struct Comparer
{
  /** \brief perform less-than comparison.
   *  \param left  left value to compare.
   *  \param right right value to compare.
   *  \return true, if left is less than right, false otherwise.
   */
  static bool lessThan(const T &left, const T &right)
  {
    return left<right;
  }
};

template<>
struct Comparer<const char*>
{
  static bool lessThan(const char *left, const char *right)
  {
    if(left==NULL)
      return true;
    if(right==NULL)
      return false;
    assert(left !=NULL);
    assert(right!=NULL);
    return strcmp(left, right)<0;
  }
};

template<>
struct Comparer<char*>
{
  static bool lessThan(const char *v1, const char *v2)
  {
    return Comparer<const char*>::lessThan(v1, v2);
  }
};

} // namespace detail
} // namespace System

#endif

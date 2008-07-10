/*
 * Enum.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ENUM_HPP_FILE
#define INCLUDE_SYSTEM_ENUM_HPP_FILE

/* public header */

#include <iostream>
#include <cassert>
#include <boost/operators.hpp>

namespace System
{

/** \brief Class wrapping around user-specified enum.
 *
 *  reference usage:
 *
 *  \code
 *
 *   struct MyEnumToWrap
 *   {
 *     typedef enum
 *     {
 *       A,
 *       B,
 *       C
 *     } Type;
 *   };
 *
 *   // [...]
 *
 *   typedef System::Enum<MyEnumToWrap> Enum1;
 *
 *   // [...]
 *
 *   Enum1 e;
 *
 *  \endcode
 *
 */
template<typename E>
class Enum: public E,
            public boost::equality_comparable< Enum<E> >
{
public:
  /** \brief ThisType typedef.
   */
  typedef Enum<E>          TType;
  /** \brief EnumType typedef.
   */
  typedef typename E::Type EType;

  /** \brief construction from enum.
   *  \param e enum to be constructed from.
   */
  inline Enum(const EType& e):      // 'explicit' is not welcomed here
    _e(e)
  {
  }

  /** \brief assignment from pure enum.
   *  \param e enum value to assign.
   *  \return this refference.
   */
  inline const TType& operator=(const EType& e)
  {
    _e=e;
    return *this;
  }

  /** \brief comparison of two classes.
   *  \param t enum to comapre with.
   *  \return true if enums are equal.
   */
  inline bool operator==(const TType& t) const
  {
    return _e==t._e;
  }
  /** \brief compare enum class with enum value.
   *  \param e enum value to campare with.
   *  \return true is values are the same.
   */
  inline bool operator==(const EType& e) const
  {
    return _e==e;
  }

  /** \brief explicit convertion is prefered since implicit
   *         might cause compiler confusions when comparing
   *         with raw int values.
   *  \return enum value as integer.
   */
  inline long toInt(void) const
  {
    return _e;
  }

private:
  typename E::Type _e;
}; // class Enum

} // namespace System

#endif


/*
 * Enum.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ENUM_HPP_FILE
#define INCLUDE_SYSTEM_ENUM_HPP_FILE

/* public header */

#include <iostream>
#include <assert.h>
#include <boost/operators.hpp>

namespace System
{

/*
 * Enum<>
 *
 * Class wrapping around user-specified enum.
 *
 * usage:
 *
 *
 * struct MyEnumToWrap
 * {
 *   typedef enum
 *   {
 *     A,
 *     B,
 *     C
 *   } Type;
 * };
 *
 * // [...]
 *
 * typedef System::Enum<MyEnumToWrap> Enum1;
 *
 * // [...]
 *
 * Enum1 e;
 *
 */
template<typename E>
class Enum: public E,
            public boost::equality_comparable< Enum<E> >
{
public:
  // some useful typedefs.
  typedef Enum<E>          TType;   // ThisType
  typedef typename E::Type EType;   // EnumType

  // construction
  inline Enum(const EType& e):      // 'explicit' is not welcomed here
    _e(e)
  {
  }

  // assignment
  inline const TType& operator=(const EType& e)
  {
    _e=e;
    return *this;
  }

  // comparison
  inline bool operator==(const TType& t) const
  {
    return _e==t._e;
  }
  inline bool operator==(const EType& e) const
  {
    return _e==e;
  }

  // explicit convertion is prefered since implicit
  // one might cause compiler confusions when comparing
  // with raw int values.
  inline int toInt(void) const
  {
    return static_cast<int>(_e);
  }

private:
  typename E::Type _e;
}; // class Enum

} // namespace System

#endif


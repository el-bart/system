/*
 * IterableEnum.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ITERABLEENUM_HPP_FILE
#define INCLUDE_SYSTEM_ITERABLEENUM_HPP_FILE

/* public header */

#include <boost/operators.hpp>
#include <boost/static_assert.hpp>
#include <cassert>

#include "System/Enum.hpp"


namespace System
{

/** \brief Class wrapping around user-specified enum that
 *         has continous numering. it can be enumerable then.
 *
 *  reference usage:
 *
 *  \code
 *
 *   struct MyEnumToWrap
 *   {
 *     // note that values have to be continues and increasing
 *     // from Min to Max!
 *     typedef enum
 *     {
 *       A=3,
 *       B=4,
 *       C=5
 *     } Type;
 *     enum { Min=A };
 *     enum { Max=C };
 *   };
 *
 *   // [...]
 *
 *   typedef System::IterableEnum<MyEnumToWrap> IterableEnum1;
 *
 *   // [...]
 *
 *   IterableEnum1 e;
 *
 *  \endcode
 *
 */
template<typename E>
class IterableEnum: public Enum<E>
{
public:
  /** \brief ThisType typedef.  */
  typedef IterableEnum<E>       TType;
  /** \brief BaseType typedef.  */
  typedef Enum<E>               BType;
  /** \brief EnumType typedef.  */
  typedef typename BType::EType EType;

  /** \brief const iterator definition.  */
  class const_iterator: public boost::equality_comparable<const_iterator>
  {
  public:
    const_iterator(void):
      _e( static_cast<EType>( static_cast<long>(E::Min) ) )
    {
      check(_e);
    }
    explicit const_iterator(const EType e):
      _e(e)
    {
      check(_e);
    }

    EType operator*(void) const
    {
      check(_e);
      return _e;
    }

    bool operator==(const const_iterator &it) const
    {
      check(_e);
      check(it._e);
      return _e==it._e;
    }

    // pre-incrementation
    const const_iterator &operator++(void)
    {
      check(_e);
      _e=static_cast<EType>(_e+1);
      check(_e);
      return *this;
    }
    // post-incrementation
    const_iterator operator++(int)
    {
      check(_e);
      const const_iterator tmp=*this;
      _e=static_cast<EType>(_e+1);
      check(_e);
      return tmp;
    }

  private:
    void check(const EType e) const
    {
      assert( E::Min              <=static_cast<long>(e) );
      // Max+1 since const_iterator may represent end()
      // iterator as well!
      assert( static_cast<long>(e)<=E::Max+1             );
    }
    EType _e;
  }; // class const_iterator

  /** \brief gives size of container.  */
  enum { Size=E::Max-E::Min+1 };

  // ensure that Min value is not greater than Max value.
  // cast here suppress warning when E is decalred in
  // unnamed namespace.
  BOOST_STATIC_ASSERT( static_cast<long>(E::Min)<=
                       static_cast<long>(E::Max)   );

  /** \brief construction from enum.
   *  \param e enum to be constructed from.
   */
  template<typename T>
  inline IterableEnum(const T t):   // 'explicit' is not welcomed here
    BType(t)
  {
    check(t);
  }

  /** \brief  returns iterator to enum's begin
   *  \return begin iterator.
   */
  inline const_iterator begin(void) const
  {
    const EType val=static_cast<EType>( static_cast<long>(E::Min)+0 );
    return const_iterator(val);
  }

  /** \brief  returns iterator to enum's end
   *  \return end iterator.
   */
  inline const_iterator end(void) const
  {
    const EType val=static_cast<EType>( static_cast<long>(E::Max)+1 );
    return const_iterator(val);
  }

  /** \brief  computes numer of values in enum.
   *  \return number of elements between Min and Max.
   */
  inline size_t size(void) const
  {
    return Size;
  }

private:
  template<typename T>
  void check(const T t) const
  {
    check( t.toLong() );
  }
  void check(const EType e) const
  {
    check( static_cast<long>(e) );
  }
  void check(const long l) const
  {
    assert( E::Min<=l );
    assert( l<=E::Max );
  }
}; // class IterableEnum

} // namespace System

#endif


/*
 * ScopedCustomPointer.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_SCOPEDCUSTOMPOINTER_HPP_FILE
#define INCLUDE_SYSTEM_SCOPEDCUSTOMPOINTER_HPP_FILE

#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>
#include <boost/type_traits/add_const.hpp>
#include <cassert>

namespace System
{

/** \brief boost::scoped_ptr<> equivalent for types with custom deallocators.
 *  \param T           type of element, that pointer to will be held.
 *  \param deallocator deallocating call.
 */
template<typename T, void(*deallocator)(T *t)>
class ScopedCustomPointer: private boost::noncopyable,
                           public  boost::less_than_comparable< ScopedCustomPointer<T, deallocator> >,
                           public  boost::equivalent<           ScopedCustomPointer<T, deallocator> >,
                           public  boost::equality_comparable<  ScopedCustomPointer<T, deallocator> >

{
public:
  /** \brief type of this object. */
  typedef ScopedCustomPointer<T, deallocator> this_type;
  /** \brief type of element held inside. */
  typedef T                                   element_type;
  /** \brief type of element held inside. */
  typedef T                                   value_type;
  /** \brief type of pointer to element held inside. */
  typedef T*                                  pointer;
  /** \brief type of reference to element held inside. */
  typedef T&                                  reference;

  /** \brief gets ownership of given object.
   *  \param t pointer to take ownership of.
   */
  explicit ScopedCustomPointer(pointer t):
    t_(t)
  {
  }
  /** \brief deallocates pointer held inside.
   */
  ~ScopedCustomPointer(void)
  {
    if(t_!=NULL)
      (*deallocator)(t_);
  }

  /** \brief comapre pointers.
   *  \param other element to compare with.
   *  \return true if this pointer is less then other, false otherwise.
   */
  bool operator<(const this_type &other) const
  {
    return get()<other.get();
  }

  /** \brief arrow operator.
   *  \return const pointer to this.
   */
  typename boost::add_const<pointer>::type operator->(void) const
  {
    return get();
  }
  /** \brief arrow operator.
   *  \return pointer to this.
   */
  pointer operator->(void)
  {
    return get();
  }

  /** \brief dereference operator.
   *  \return const reference to this.
   */
  const reference operator*(void) const
  {
    return *get();
  }
  /** \brief dereference operator.
   *  \return reference to this.
   */
  reference operator*(void)
  {
    return *get();
  }

  /** \brief gets pointer held inside - non-const version.
   *  \return owned pointer.
   */
  pointer get(void)
  {
    return t_;
  }
  /** \brief gets pointer held inside - const version.
   *  \return owned pointer.
   */
  typename boost::add_const<pointer>::type get(void) const
  {
    return t_;
  }

  /** \brief swap content of this and other pointers.
   *  \param other element to swap content with.
   */
  void swap(this_type &other)
  {
    pointer tmp=other.release();
    assert( other.get()==NULL );
    other.t_=get();
    t_=tmp;
  }

  /** \brief releases pointer held inside.
   *  \return pointer, that is no longer owned by this object.
   */
  pointer release(void)
  {
    pointer tmp=t_;
    t_=NULL;
    return tmp;
  }

private:
  pointer t_;
}; // class ScopedCustomPointer

} // namespace System

#endif

/*
 * DivingStack.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_DIVINGSTACK_HPP_FILE
#define INCLUDE_SYSTEM_DIVINGSTACK_HPP_FILE

/* public header */

#include <deque>
#include <cassert>

#include "System/Exception.hpp"

namespace System
{

/** \brief diving stack of a given size implementaion.
 *
 *  diving stack is a structure aving given ammount of elements at maximum.
 *  when trying to add new element last one is lost.
 */
template<typename T>
class DivingStack
{
private:
  typedef std::deque<T> Queue;

public:
  struct ExceptionInvalidMaximumSize: public Exception
  {
    explicit ExceptionInvalidMaximumSize(const Location &where):
      Exception(where, "diving stack's maximum size must be positive number")
    {
    }
  }; // struct ExceptionInvalidMaximumSize

  struct ExceptionDifferentMaximumSizes: public Exception
  {
    explicit ExceptionDifferentMaximumSizes(const Location &where, size_t from, size_t to):
      Exception(where, cc("during assignment both stacks must have the same maximum "
                          "number of elements (assigning stack of size ", from,
                          " to stack of size ", to, ")") )
    {
    }
  }; // struct ExceptionDifferentMaximumSizes


  /** \brief type of elements held inside. */
  typedef T                              element_type;
  /** \brief type of elements (values) held inside. */
  typedef element_type                   value_type;
  /** \brief iterator through the sequence. */
  typedef typename Queue::iterator       iterator;
  /** \brief const iterator through the sequence. */
  typedef typename Queue::const_iterator const_iterator;

  explicit DivingStack(size_t maxSize):
    maxSize_(maxSize)
  {
    if(maxSize_==0)
      throw ExceptionInvalidMaximumSize(SYSTEM_SAVE_LOCATION);
  }

  // NOTE: default copty c-tor is fine here.

  const DivingStack<value_type> &operator=(const DivingStack<value_type> &other)
  {
    if(this==&other)
      return *this;
    if( maxSize()!=other.maxSize() )
      throw ExceptionDifferentMaximumSizes(SYSTEM_SAVE_LOCATION, other.maxSize(), maxSize() );
    // perform the assignment
    q_      =other.q_;
    maxSize_=other.maxSize_;
    return *this;
  }

  size_t size(void) const
  {
    return q_.size();
  }

  size_t maxSize(void) const
  {
    assert(maxSize_>0u);
    return maxSize_;
  }

  bool empty(void) const
  {
    return size()==0u;
  }

  const value_type &top(void) const
  {
    assert( !empty() );
    assert( size()<=maxSize() );
    return q_.back();
  }

  value_type &top(void)
  {
    assert( !empty() );
    assert( size()<=maxSize() );
    return q_.back();
  }

  void pop(void)
  {
    assert( !empty() );
    assert( size()<=maxSize() );
    q_.pop_back();
  }

  void push(const value_type &t)
  {
    if( size()==maxSize_ )
      q_.pop_front();
    assert( size()<maxSize() );
    q_.push_back(t);
    assert( !empty() );
    assert( size()<=maxSize() );
  }

  iterator begin(void)
  {
    return q_.begin();
  }

  iterator end(void)
  {
    return q_.end();
  }

  const_iterator begin(void) const
  {
    return q_.begin();
  }

  const_iterator end(void) const
  {
    return q_.end();
  }

private:
  size_t maxSize_;
  Queue  q_;
}; // class DivingStack

} // namespace System

#endif


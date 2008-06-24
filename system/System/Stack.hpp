/*
 * Stack.hpp
 *
 * implementation of stack, basing on STL's deque.
 *
 */
#ifndef INCLUDE_SYSTEM_STACK_HPP_FILE
#define INCLUDE_SYSTEM_STACK_HPP_FILE

/* public header */

#include <deque>

#include "System/Exception.hpp"


namespace System
{

/**
 * template class of elements formed in stack.
 */
template<typename T>
class Stack
{
public:
  /**
   * puts copy of a given element on stack's top.
   * \param t element to be put on top.
   */
  void push(const T &t)
  {
    elems_.push_back(t);                // put on the top
  }

  /**
   * removes element from top of stack and return its copy.
   * throws when called for empty stack.
   * \return element from top of the stack.
   */
  T pop(void)
  {
    const T t=get();                    // get element
    elems_.pop_back();                  // remove it from the queue
    return t;                           // return its value
  }

  /**
   * returns element from the top, without destroing it.
   * throws if stack is empty.
   * \return copy of element from the top.
   */
  T get(void)
  {
    if( empty() )
      throw Exception("System::Stack::get(): stack is empty");
    return elems_[elems_.size()-1];  // get element
  }

  /**
   * checks if stack is empty.
   * \return true if stack is empty.
   */
  bool empty(void) const
  {
    return elems_.empty();
  }

private:
  std::deque<T> elems_;
}; // class Stack

} // namespace System

#endif

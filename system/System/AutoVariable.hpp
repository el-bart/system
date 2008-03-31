/*
 * AutoVariable.hpp
 *
 * auto_ptr<>-like class wrapper, for given user
 * data-specific thin-wrapper. it allows to easy
 * construction of ownership-passing classes via
 * inheritance.
 *
 */
#ifndef INCLUDE_SYSTEM_AUTOVARIABLE_HPP_FILE
#define INCLUDE_SYSTEM_AUTOVARIABLE_HPP_FILE

/* public header */

#include "System/Exception.hpp"

namespace System
{
/** \brief this is class holding user data type T, to
 *         behave like std::auto_ptr<> when copying.
 *
 *  this is example code showing how to write
 *  data-specific classes. assume MyT to be class
 *  to be held (notice that it does NOT dealocate()'s
 *  object itself!).
 *
 *  \code
 *
 *   class SomeAutoHolder
 *   {
 *   public:
 *     typedef MyT TValue;
 *     explicit SomeAutoHolder(TValue v);
 *     SomeAutoHolder(void);
 *
 *     TValue get(void) const;  // return current value
 *     void dealocate(void);    // dealocate resource being held
 *
 *   private:
 *     TValue _v;
 *   };
 *
 */
template<typename T>
class AutoVariable
{
public:
  // this makes life easier:
  typedef typename T::TValue TValue;

  /** \brief constructs class from user data-holder.
   *  \param t user data holder.
   */
  explicit AutoVariable(T t):
    _t(t)
  {
  }

  /** \brief constructs class from user-data.
   *  \param v raw user data.
   */
  explicit AutoVariable(TValue v):
    _t(v)
  {
  }

  /** \brief default constructor, creating empty-holding
   *         object.
   */
  AutoVariable(void)
  {
  }

  /** \brief copy constructor.
   *  \param av class to take ownership from.
   */
  AutoVariable(AutoVariable &av):
    _t(av._t)
  {
    av._t.dealocate();      // ownership has been already passed
  }
  /** \brief destructor.
   */
  ~AutoVariable(void)
  {
    _t.dealocate();
  }

  /** \brief returns user data type.
   *  \return user data in raw form.
   */
  inline TValue get(void) const
  {
    return _t.get();
  }

  void reset(TValue v)
  {
    _t.dealocate();
    _t=T(v);
  }

  TValue release(void)
  {
    TValue v=_t.get();
    _t=T();
    return v;
  }

  /** \brief convertion operator to helper object.
   *  \returns temporary object with ownership.
   */
  operator T(void)
  {
    T t=_t;
    _t.dealocate();
    return t;
  }

  /** \brief assignment operator.
   *  \param av object to take ownership from.
   *  \returns reference to current object.
   */
  AutoVariable& operator=(AutoVariable &av)
  {
    _t=av._t;
    av._t.dealocate();
    return *this;
  }

  /** \brief checks if object is initialized.
   *  \return true if object is initialized.
   */
  bool isInitialized(void) const
  {
    static const T invalid;
    return _t.get()!=invalid.get();
  }

private:
  T _t;
}; // class AutoVariable

} // namespace System

#endif


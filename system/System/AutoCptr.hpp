/*
 * AutoCptr.hpp
 *
 * class behaving like an auto_ptr<> for
 * C-allocated pointer.
 *
 */
#ifndef INCLUDE_SYSTEM_AUTOCPTR_HPP_FILE
#define INCLUDE_SYSTEM_AUTOCPTR_HPP_FILE

/* public header */

#include <stdio.h>
#include <unistd.h>
#include <boost/operators.hpp>

#include "System/AutoVariable.hpp"

namespace System
{

/** \brief helper class for internal usage in AutoCptr.
 */
template<typename T>
class CptrHolder
{
public:
  /** \brief typedef for value type being held.
   */
  typedef T* TValue;
  /** \brief constructor setting pointer value to be held.
   *  \param v pointer to be held.
   */
  explicit CptrHolder(TValue v=NULL):
    _v(v)
  {
  }
  /** \brief returns pointer.
   *  \return pointer being held.
   */
  inline TValue get(void) const
  {
    return _v;
  }
  /** \brief frees pointer held inside.
   */
  void dealocate(void)
  {
    if(_v!=NULL)
    {
      free(_v);
      _v=NULL;
    }
  }

private:
  TValue _v;
}; // class CptrHolder


/** \brief auto_ptr<>-like class for holding C-allocated pointers.
 */
template<typename T>
class AutoCptr: public boost::equality_comparable< AutoCptr<T> >,
                public System::AutoVariable< CptrHolder<T> >
{
private:
  typedef CptrHolder<T>                 THolder;
  typedef System::AutoVariable<THolder> AutoBase;

public:
  /** \brief pointer type held inside.
   */
  typedef typename THolder::TValue TPtr;

  /** \brief create C-pointer holder.
   *  \param fs pointer to be held.
   */
  explicit AutoCptr(TPtr fs=NULL):
    AutoBase(fs)
  {
  }
}; // class AutoCptr

} // namespace System

#endif


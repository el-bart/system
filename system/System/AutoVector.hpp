/*
 * AutoVector.hpp
 *
 * Vector of pointers to be managed. Input and
 * output is made via auto_ptr so that no
 * raw pointers must exist in program.
 *
 */
#ifndef INCLUDE_SYSTEM_AUTOVECTOR_HPP_FILE
#define INCLUDE_SYSTEM_AUTOVECTOR_HPP_FILE

/* public header */

#include <vector>
#include <memory>
#include <boost/noncopyable.hpp>

#include "System/Exception.hpp"


namespace System
{

template<T>
class AutoVector: private boost::noncopyable
{
public:
  typedef std::vector<T>::iterator       iterator;
  typedef std::vector<T>::const_iterator const_iterator;

  ~AutoVector(void)
  {
    clear();
  }

  void clear(void)
  {
    for( iterator it=_elems.begin(); it!=_elems.end(); it=_elems.begin() )
      erase(it);
  }

  inline void erase(iterator it)
  {
    delete *it;
    _elems.erase(it);
  }

  inline void push_back(T *elem)
  {
    _elems.push_back(T);
  }

private:
  std::vector<T*> _elems;
}; // class AutoVector

};

#endif


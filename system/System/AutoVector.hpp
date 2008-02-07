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

template<TElem>
class AutoVector: private boost::noncopyable
{
public:
  typedef std::vector<TElem>::iterator       iterator;
  typedef std::vector<TElem>::const_iterator const_iterator;

  ~AutoVector(void)
  {
    clear();
  };

  void clear(void)
  {
    for(iterator it=_elems.begin(); it!=_elems.end(); ++it)
      erase(it);
  };

  inline void erase(iterator it)
  {
    delete *it;
    _elems.erase(it);
  };

private:
  std::vector<TElem*> _elems;
}; // class AutoVector

};

#endif


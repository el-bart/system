/*
 * AtExitResourceDealocator.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_ATEXITRESOURCEDEALOCATOR_HPP_FILE
#define INCLUDE_SYSTEM_ATEXITRESOURCEDEALOCATOR_HPP_FILE

/* public header */

#include <memory>
#include <boost/noncopyable.hpp>


namespace System
{

/** \brief resource's deallocator interface.
 *
 * base class for all deallocators that are to be
 * registered with AtExit class.
 */
struct AtExitResourceDeallocator: private boost::noncopyable
{
  /** \brief virtual destructor for polimorphic collections.
   */
  virtual ~AtExitResourceDeallocator(void)
  {
  }
  /** \brief resource deallocating method.
   *
   * method that is called by AtExit when program quits.
   * treat it the same way as destructors - it should NOT
   * throw.
   * it is guaranteed that AtExit will call this method
   * exactly once for each object, when quiting.
   */
  virtual void deallocate(void)=0;
}; // struct AtExitResourceDeallocator

} // namespace System

#endif


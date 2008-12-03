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

/** \brief resource's dealocator interface.
 *
 * base class for all dealocators that are to be
 * registered with AtExit class.
 */
struct AtExitResourceDealocator: private boost::noncopyable
{
  /** \brief virtual destructor for polimorphic collections.
   */
  virtual ~AtExitResourceDealocator(void)
  {
  }
  /** \brief resource dealocating method.
   *
   * method that is called by AtExit when program quits.
   * treat it the same way as destructors - it should NOT
   * throw.
   * it is guaranteed that AtExit will call this method
   * exactly once for each object, when quiting.
   */
  virtual void dealocate(void)=0;
}; // struct AtExitResourceDealocator

} // namespace System

#endif


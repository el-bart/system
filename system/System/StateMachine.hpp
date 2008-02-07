/*
 * StateMachine.hpp
 *
 * easy to use and implement general purpose state
 * machine implementation.
 *
 */
#ifndef INCLUDE_SYSTEM_STATEMACHINE_HPP_FILE
#define INCLUDE_SYSTEM_STATEMACHINE_HPP_FILE

/* public header */

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <assert.h>

#include "System/Enum.hpp"
#include "System/Exception.hpp"


namespace System
{

// base class for all states. this object MUST BE
// STATELES in order to work properly after reset!
template<typename TEnum>
struct StateBase
{
public:
  virtual ~StateBase(void)
  {
  }

  // step from this state to another.
  // next state should be returned from this call.
  virtual TEnum doStep(void) = 0;
}; // struct StateBase


//
// class implementing the state machine itself.
// this class should be deriven from. handlers
// for ALL states must be given in constructor
// of derived class via addState() method.
// notice that each enum must have uniq value,
// first one starting with 0 and last one with n-1
// where n is number of states.
//
template<typename TEnum>
class StateMachine: private boost::noncopyable
{
public:
  typedef StateBase<TEnum>        StateType;
  typedef std::vector<StateType*> StateCollection;

  // sets the state from which state machine
  // should start
  inline StateMachine(const TEnum startState, const size_t statesCount):
    _resetState  ( startState ),
    _currentState( _resetState  ),
    _states      ( statesCount )
  {
    assert( _states.size()==statesCount );
    // reset whole state machine
    for(typename StateCollection::iterator it=_states.begin();
        it!=_states.end();
        ++it)
      *it=NULL;
  }

  // reset state machine
  inline void reset(void)
  {
    _currentState=_resetState;
  }

  inline TEnum currentState(void) const
  {
    return _currentState;
  }

  // perform single step of state machine and return
  // current state it is in
  inline TEnum step(void)
  {
    // get current state from map:
    assert( _currentState.toInt()>=0 );
    const unsigned int curSt=_currentState.toInt();
    assert( /* 0<=curSt && */ curSt<_states.size() );
    StateType *se=_states[curSt];
    assert( se!=NULL );
    _currentState=se->doStep();     // perform step to next one
    return _currentState;           // return state reached
  }

protected:
  // this should be used by derived class to add
  // handlers for a given states
  inline void addState(const TEnum state, StateType *handler)
  {
    assert( state.toInt()>=0 );
    const unsigned int stateInt=state.toInt();
    assert( /* 0<=stateInt && */ stateInt<_states.size() ||
            !"index out of bounds - possibly number of enries is too small" );
    assert( _states[stateInt]==NULL ||
            !"given state is already handled");     // no overwriting
    _states[stateInt]=handler;
  }

private:
  const TEnum     _resetState;
  TEnum           _currentState;
  StateCollection _states;
}; // class StateMachine

} // namespace System

#endif


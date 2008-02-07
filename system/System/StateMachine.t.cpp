/*
 * StateMachine.t.cpp
 *
 * test set for StateMachine.
 *
 */
#include <tut.h>

#include "System/StateMachine.hpp"


namespace System
{

struct StateMachineTestData
{
  struct MyEnum
  {
    typedef enum
    {
      STATE_A=0,
      STATE_B=1,
      STATE_C=2,
    } Type;
  };
  typedef System::Enum<MyEnum> StateEnum;

  struct StateA: public System::StateBase<StateEnum>
  {
    virtual StateEnum doStep(void)
    {
      return StateEnum::STATE_B;
    }
  };
  struct StateB: public System::StateBase<StateEnum>
  {
    virtual StateEnum doStep(void)
    {
      return StateEnum::STATE_C;
    }
  };
  struct StateC: public System::StateBase<StateEnum>
  {
    virtual StateEnum doStep(void)
    {
      return StateEnum::STATE_C;
    }
  };

  class TestStateMachine: public StateMachine<StateEnum>
  {
  public:
    TestStateMachine(void):
      StateMachine<StateEnum>(StateEnum::STATE_A, 3)
    {
      addState(StateEnum::STATE_A, &a);
      addState(StateEnum::STATE_B, &b);
      addState(StateEnum::STATE_C, &c);
    }
  private:
    StateA a;
    StateB b;
    StateC c;
  };


  // test data itself :)
  StateMachineTestData(void)
  {
    _vsm=&_sm;
  }

  TestStateMachine         _sm;
  StateMachine<StateEnum> *_vsm;
};

} // namespace System


namespace tut
{
typedef System::StateMachineTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/StateMachine");
}



namespace tut
{

// check default state
template<>
template<>
void testObj::test<1>(void)
{
  ensure( _vsm->currentState()==StateEnum::STATE_A );
}

// perform single stepping
template<>
template<>
void testObj::test<2>(void)
{
  ensure( _vsm->step()==StateEnum::STATE_B );
  ensure( _vsm->step()==StateEnum::STATE_C );
  ensure( _vsm->step()==StateEnum::STATE_C );
}

// reset machine in work
template<>
template<>
void testObj::test<3>(void)
{
  ensure( _vsm->step()==StateEnum::STATE_B );
  _vsm->reset();
  ensure( _vsm->step()==StateEnum::STATE_B );
}

} // namespace tut


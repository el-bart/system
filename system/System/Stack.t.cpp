/*
 * Stack.t.cpp
 *
 */
#include <tut.h>
#include <string>

#include "System/Stack.hpp"

namespace System
{
struct StackTestData
{
};
} // namespace System


namespace tut
{
typedef System::StackTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/Stack");
}

using namespace std;
using namespace System;

namespace tut
{

// constructor test
template<>
template<>
void testObj::test<1>(void)
{
  Stack<int>    is;
  ensure("new stack is not empty (1)", is.empty() );

  Stack<string> ss;
  ensure("new stack is not empty (2)", ss.empty() );
}

// test addition and poping (usual case)
template<>
template<>
void testObj::test<2>(void)
{
  Stack<double> sd;
  ensure("precondition failed", sd.empty() );
  // pushing
  sd.push(3.14);
  ensure("non-empty stack reports as empty (1)", sd.empty()==false );
  sd.push(2.79);
  ensure("non-empty stack reports as empty (2)", sd.empty()==false );
  // poping
  ensure("invalid value has been read (1)", sd.pop()==2.79);
  ensure("non-empty stack reports as empty (3)", sd.empty()==false );
  ensure("invalid value has been read (2)", sd.pop()==3.14);
  // final ensurance
  ensure("empty stack reports as non-empty", sd.empty() );
}

// test if pop from empty queue throws
template<>
template<>
void testObj::test<3>(void)
{
  Stack<string> ss;
  try
  {
    ss.pop();       // should throw
    fail("pop() did not throw on empty queue");
  }
  catch(const Exception &ex)
  {
    // this is expected
  }
}

// test if get from empty queue throws
template<>
template<>
void testObj::test<4>(void)
{
  Stack<string> ss;
  try
  {
    ss.get();       // should throw
    fail("get() did not throw on empty queue");
  }
  catch(const Exception &ex)
  {
    // this is expected
  }
}

// test if get() does not remove element from stack
template<>
template<>
void testObj::test<5>(void)
{
  Stack<string> ss;
  ss.push("test1");
  ss.push("test2");

  ensure("get() returns invalid element (1)", ss.get()=="test2");
  ensure("get() changes stack (1)",           ss.get()=="test2");
  ss.pop();
  ensure("get() returns invalid element (2)", ss.get()=="test1");
  ensure("get() changes stack (2)",           ss.get()=="test1");
}

} // namespace tut


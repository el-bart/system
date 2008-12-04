/*
 * AtExitImpl.t.cpp
 *
 */
#include <tut.h>
#include <vector>

#include "System/AtExitImpl.hpp"

namespace System
{

struct AtExitImplTestData
{
  AtExitImplTestData(void)
  {
  }

  std::vector<int> out_;
};

} // namespace System


namespace tut
{
typedef System::AtExitImplTestData TestClass;
typedef test_group<TestClass> factory;
typedef factory::object testObj;
} // namespace tut


namespace
{
tut::factory tf("System/AtExitImpl");
}

using namespace std;
using namespace System;

// unnamed namespace for helper objects
namespace
{

template<int N>
struct TestDealocator: public AtExitResourceDealocator
{
  explicit TestDealocator(vector<int> *out):
    out_(out)
  {
    assert(out_!=NULL);
  }

  virtual void dealocate(void)
  {
    out_->push_back(N);
  }

  vector<int> *out_;
}; // struct TestDealocator

} // unnamed namespace

namespace tut
{

// test empty run
template<>
template<>
void testObj::test<1>(void)
{
  AtExitImpl impl;
  impl.dealocateAll();
}

// test dealocation of some elements
template<>
template<>
void testObj::test<2>(void)
{
  AtExitImpl   impl;
  // create
  AtExit::Tptr res1( new TestDealocator<1>(&out_) );
  AtExit::Tptr res2( new TestDealocator<2>(&out_) );
  AtExit::Tptr res3( new TestDealocator<3>(&out_) );
  // register
  impl.registerDealocator(res1);
  impl.registerDealocator(res2);
  impl.registerDealocator(res3);
  // dealocate
  impl.dealocateAll();

  // check output
  ensure_equals("invlid size of output container", out_.size(), 3);
  ensure_equals("unknown unregistration no. 1", out_[0], 3);
  ensure_equals("unknown unregistration no. 2", out_[1], 2);
  ensure_equals("unknown unregistration no. 3", out_[2], 1);
}

// test for single object
template<>
template<>
void testObj::test<3>(void)
{
  AtExitImpl   impl;
  AtExit::Tptr res( new TestDealocator<12>(&out_) );
  impl.registerDealocator(res);
  ensure("problem passing ownership to AtExitImpl", res.get()==NULL);
  impl.dealocateAll();
  // check output
  ensure_equals("invlid size of output container", out_.size(), 1);
  ensure_equals("unknown unregistration", out_[0], 12);
}

} // namespace tut

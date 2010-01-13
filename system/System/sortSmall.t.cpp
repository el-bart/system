/*
 * sortSmall.t.cpp
 *
 */
#include <tut/tut.hpp>
#include <list>
#include <vector>

#include "System/sortSmall.hpp"

using namespace System;

namespace
{
struct TestClass
{
  template<typename T>
  void check(T &tab, const T &cmp) const
  {
    const int size=sizeof(T)/sizeof(tab[0]);
    for(int i=0; i<size; ++i)
    {
      tut::ensure_equals("sorting falied",  tab[i], cmp[i]);
    }
  }

  template<typename T>
  void sortAndCheck(T &tab, const T &cmp) const
  {
    const int size=sizeof(T)/sizeof(tab[0]);
    sortSmall(tab, tab+size);
    check(tab, cmp);
  }
};

typedef TestClass                  TestClass;
typedef tut::test_group<TestClass> factory;
typedef factory::object            testObj;

factory tf("System/sortSmall");
} // unnamed namespace


namespace tut
{

// test sorting one element
template<>
template<>
void testObj::test<1>(void)
{
  int       tab[]={1};
  const int cmp[]={1};
  sortAndCheck(tab, cmp);
}

// test sort already sorted 2 elements
template<>
template<>
void testObj::test<2>(void)
{
  int       tab[]={1, 2};
  const int cmp[]={1, 2};
  sortAndCheck(tab, cmp);
}

// test sort already sorted 3 elements
template<>
template<>
void testObj::test<3>(void)
{
  int       tab[]={1, 2, 3};
  const int cmp[]={1, 2, 3};
  sortAndCheck(tab, cmp);
}

// check sort already sorted 4 elements
template<>
template<>
void testObj::test<4>(void)
{
  int       tab[]={1, 2, 3, 4};
  const int cmp[]={1, 2, 3, 4};
  sortAndCheck(tab, cmp);
}

// sort reverse-sorted 2-elements
template<>
template<>
void testObj::test<5>(void)
{
  int       tab[]={3, 2};
  const int cmp[]={2, 3};
  sortAndCheck(tab, cmp);
}

// sort reverse-sorted 3-elements
template<>
template<>
void testObj::test<6>(void)
{
  int       tab[]={3, 2, 1};
  const int cmp[]={1, 2, 3};
  sortAndCheck(tab, cmp);
}

// sort reverse-sorted 4-elements
template<>
template<>
void testObj::test<7>(void)
{
  int       tab[]={4, 3, 2, 1};
  const int cmp[]={1, 2, 3, 4};
  sortAndCheck(tab, cmp);
}

// sort almost-sorted long table
template<>
template<>
void testObj::test<8>(void)
{
  int       tab[]={2, 5, 8, 10, 6, 10, 20};
  const int cmp[]={2, 5, 6, 8, 10, 10, 20};
  sortAndCheck(tab, cmp);
}

// test sorting std::vector of elements
template<>
template<>
void testObj::test<9>(void)
{
  std::vector<long> v;
  v.push_back(6);
  v.push_back(5);
  v.push_back(3);
  v.push_back(4);
  sortSmall( v.begin(), v.end() );
  ensure_equals("invalid element 0", v[0], 3);
  ensure_equals("invalid element 1", v[1], 4);
  ensure_equals("invalid element 2", v[2], 5);
  ensure_equals("invalid element 3", v[3], 6);
}

// test sorting std::list of elements
template<>
template<>
void testObj::test<10>(void)
{
  std::list<long> l;
  l.push_back(6);
  l.push_back(5);
  l.push_back(3);
  l.push_back(4);
  sortSmall( l.begin(), l.end() );
  std::list<long>::const_iterator it=l.begin();
  ensure_equals("invalid element 0", *it++, 3);
  ensure_equals("invalid element 1", *it++, 4);
  ensure_equals("invalid element 2", *it++, 5);
  ensure_equals("invalid element 3", *it++, 6);
}

namespace
{
struct MyStruct
{
  MyStruct(int id):
    id_(id)
  {
  }

  int id_;
}; // struct MyStruct

struct MyStructSWO
{
  bool operator()(const MyStruct &left, const MyStruct &right) const
  {
    return left.id_<right.id_;
  }
}; // struct MyStructSWO
} // unnamed namespace

// test sorking elements with own SWO
template<>
template<>
void testObj::test<11>(void)
{
  std::vector<MyStruct> v;
  v.push_back(6);
  v.push_back(5);
  v.push_back(3);
  v.push_back(4);
  sortSmall( v.begin(), v.end(), MyStructSWO() );
  ensure_equals("invalid element 0", v[0].id_, 3);
  ensure_equals("invalid element 1", v[1].id_, 4);
  ensure_equals("invalid element 2", v[2].id_, 5);
  ensure_equals("invalid element 3", v[3].id_, 6);
}

namespace
{
struct MyStructStr
{
  MyStructStr(const char *str):
    str_(str)
  {
  }

  std::string str_;
}; // struct MyStructStr

struct MyStructStrSWO
{
  bool operator()(const MyStructStr &left, const MyStructStr &right) const
  {
    return left.str_.length()<right.str_.length();
  }
}; // struct MyStructStrSWO
} // unnamed namespace

// test if sorting is stable
template<>
template<>
void testObj::test<12>(void)
{
  std::vector<MyStructStr> v;
  v.push_back("has");
  v.push_back("alice");
  v.push_back("doom");
  v.push_back("winny");
  v.push_back("cat");
  sortSmall( v.begin(), v.end(), MyStructStrSWO() );
  ensure_equals("invalid element 0", v[0].str_, "has");
  ensure_equals("invalid element 1", v[1].str_, "cat");
  ensure_equals("invalid element 2", v[2].str_, "doom");
  ensure_equals("invalid element 3", v[3].str_, "alice");
  ensure_equals("invalid element 3", v[4].str_, "winny");
}


} // namespace tut

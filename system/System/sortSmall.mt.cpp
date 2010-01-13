/*
 * sortSmall.mt.cpp
 *
 */
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sys/time.h>

#include "System/sortSmall.hpp"

using namespace std;
using namespace System;

typedef vector<int> TestVector;
const int repeats=1E6;

struct Timer
{
  Timer(void):
    total_(0)
  {
  }

  void start(void)
  {
    gettimeofday(&start_, NULL);
  }

  void stop(void)
  {
    gettimeofday(&stop_, NULL);
    total_+=sec(stop_)-sec(start_);
  }

  void print(const char *name) const
  {
    printf("%s: %2.3f[s]\n", name, total_);
  }

private:
  double sec(const timeval &t) const
  {
    return (double) t.tv_sec +
           (double)(t.tv_usec)/1E6;
  }

  timeval start_;
  timeval stop_;
  double  total_;
};

void sortSmall(const TestVector &v)
{
  Timer t;
  for(int i=0; i<repeats; ++i)
  {
    TestVector tmp=v;
    t.start();
    std::sort( tmp.begin(), tmp.end() );
    t.stop();
  }
  t.print("sortSmall");
}

void sortStl(const TestVector &v)
{
  Timer t;
  for(int i=0; i<repeats; ++i)
  {
    TestVector tmp=v;
    t.start();
    std::sort( tmp.begin(), tmp.end() );
    t.stop();
  }
  t.print("sortSTL  ");
}

int main(int argc, char **argv)
{
  if(argc!=2)
  {
    cerr<<argv[0]<<" <elements>"<<endl;
    return 1;
  }

  TestVector v;
  for(int i=0; i<atoi(argv[1]); ++i)
    v.push_back( rand() );

  sortSmall(v);
  sortStl(v);

  return 0;
}


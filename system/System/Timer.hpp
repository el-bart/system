/*
 * Timer.hpp
 *
 */
#ifndef INCLUDE_SYSTEM_TIMER_HPP_FILE
#define INCLUDE_SYSTEM_TIMER_HPP_FILE

/* public header */

#include <sys/time.h>

namespace System
{

class Timer
{
public:
  Timer(void)
  {
    restart();
  }

  void restart(void)
  {
    gettimeofday(&start_, NULL);
  }

  double elapsed(void) const
  {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec-start_.tv_sec + (now.tv_usec-start_.tv_usec)/1000000.0;
  }
private:
  struct timeval start_;
}; // class Timer

} // namespace System

#endif

/**
 * @class Timer_impl
 * @brief Implementation for a simple countdown timer
 *
 */
#ifndef TIMER_IMPL_H
#define TIMER_IMPL_H
#include <time_utils.h>

class Timer_impl
{
public:
  /**
   * @brief Constructor. A new timer with the specified duration
   * @param duration Amount of time the timer should count down for, seconds
   */
  Timer_impl(const double duration);

private:
  /**
   * @brief m_duration Duration for the time
   */
  double m_duration;
  double m_start_time;
};

#endif

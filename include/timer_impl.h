/**
 * @class Timer_impl
 * @brief Implementation for a simple countdown timer
 *
 */
#ifndef TIMER_IMPL_H
#define TIMER_IMPL_H
#include <thread>

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
   * @brief m_duration Duration for the timer
   */
  double m_duration;

  double m_start_time;

  /**
   * @brief m_timer_thread Thread running the countdown
   */
  std::thread m_timer_thread;
};

#endif

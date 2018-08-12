/**
 * @class Timer
 * @brief A simple countdown timer
 *
 */
#ifndef TIMER_H
#define TIMER_H
#include <memory>

class Timer_impl;

class Timer
{
public:
  /**
   * @brief Constructor. A new timer with the specified duration
   * @param duration Amount of time the timer should count down for, seconds
   */
  Timer(const double duration);

private:
  /**
   * @brief m_pimpl Implementation
   */
  std::shared_ptr<Timer_impl> m_pimpl;
};

#endif

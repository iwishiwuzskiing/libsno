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

  /**
   * @brief Start the timer. Does nothing if timer is already running
   */
  void Start();

  /**
   * @brief Stop the timer. Does nothing if timer is not already running
   */
  void Stop();

  /**
   * @brief Register a function to be called when the timer times out
   */
  void Register_timeout_callback();

  /**
   * @brief Set the duration for the timer
   * @param duration New duration for the timer, seconds
   */
  void Set_duration(const double duration);

  /**
   * @brief Get the current duration of the timer
   * @return Timer duration, seconds
   */
  double Get_duration() const;

private:
  /**
   * @brief m_pimpl Implementation
   */
  std::shared_ptr<Timer_impl> m_pimpl;
};

#endif

/**
 * @brief A simple stopwatch
 */

#ifndef SO_STOPWATCH_IMPL_H
#define SO_STOPWATCH_IMPL_H
#include <chrono>

namespace so
{

class Stopwatch_impl
{
public:
  typedef std::chrono::steady_clock Clock_type;

  /**
   * @brief Constructor, a new stopwatch
   */
  Stopwatch_impl();

  /**
   * @brief Start the stopwatch. Does nothing if the stopwatch is already
   * running
   */
  void Start();

  /**
   * @brief Stop the stopwatch but do not reset the elapsed time. Does nothing
   * if the stopwatch not running
   * @return Elapsed time, seconds
   * @throws so::runtime_exception if the number of microseconds in the
   * current elapsed time cannot be represented by a double
   */
  double Stop();

  /**
   * @brief Take a split
   * @return Number of seconds since the last split, or since the stopwatch was
   * started if this is the first split. Returns 0 if the timer isn't running
   * @throws so::runtime_exception if the number of microseconds in the
   * current split cannot be represented by a double
   */
  double Split();

  /**
   * @brief Reset the stopwatch
   */
  void Reset();

  /**
   * @brief Get the current elapsed time since the stopwatch was started
   * @return Current elapsed time since the stopwatch was started, seconds
   * @throws so::runtime_exception if the number of microseconds in the
   * current elapsed time cannot be represented by a double
   */
  double Get_time();

private:

  /**
   * @brief m_start_time Time when the stopwatch started
   */
  std::chrono::time_point<Clock_type> m_start_time;

  /**
   * @brief m_last_split Time when the last split was taken
   */
  std::chrono::time_point<Clock_type> m_last_split;

  /**
   * @brief elapsed_time Last runtime of the stopwatch
   */
  double m_elapsed_time;

  /**
   * @brief m_running True if the stopwatch is running
   */
  bool m_running;

  /**
   * @brief update_elapsed_time Update the current elapsed time
   */
  void update_elapsed_time();
};

}
#endif

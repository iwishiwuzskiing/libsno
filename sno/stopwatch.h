#include <memory>

class Stopwatch_impl;

class Stopwatch
{
public:
  /**
   * @brief Constructor, a new stopwatch
   */
  Stopwatch();

  /**
   * @brief Start the stopwatch
   */
  void Start();

  /**
   * @brief Stop the stopwatch but do not reset the elapsed time
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
   * @brief m_pimpl Implementation class
   */
  std::shared_ptr<Stopwatch_impl> m_pimpl;
};

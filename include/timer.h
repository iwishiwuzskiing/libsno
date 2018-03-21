///**
// * @brief A simple timer
// */

//#ifndef TIMER_H
//#define TIMER_H
//#include <chrono>

//class Stopwatch
//{
//public:
//  /**
//   * @brief Constructor, a new stopwatch
//   * @param init Number of seconds for the stopwatch to start at
//   */
//  Stopwatch(double init = 0);

//  /**
//   * @brief Start counting time
//   * @param init Initial number of seconds for the stopwatch
//   */
//  void Start(double init = 0);

//  /**
//   * @brief Stop counting time
//   * @return Elapsed seconds
//   */
//  double Stop();

//  /**
//   * @brief Take a split
//   * @return Number of seconds since the last split, or since the stopwatch was
//   * started if this is the first split
//   */
//  double Split();

//  /**
//   * @brief Restart the stop watch
//   * @param init Number of seconds to restart at
//   * @return The number of seconds that had elapsed before the timer was
//   * restarted
//   */
//  double Reset(double init = 0);

//  /**
//   * @brief Get the current number of seconds that have elapsed since the timer
//   * was started
//   * @return
//   */
//  double Time();

//protected:

//private:
//  /**
//   * @brief m_start_time Time when the timer started
//   */
//  std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;

//  /**
//   * @brief m_last_split Time when the last split was taken
//   */
//  std::chrono::time_point<std::chrono::high_resolution_clock> m_last_split;
//};

//#endif

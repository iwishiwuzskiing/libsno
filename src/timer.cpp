#include <timer.h>
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
using namespace std::chrono;
/**
 * @brief Constructor, a new stopwatch
 * @param init Number of seconds for the stopwatch to start at
 */
Stopwatch::Stopwatch(double init)
  :
    m_start_time(),
    m_last_split(m_start_time)
{
  std::chrono::time_point<std::chrono::high_resolution_clock> tp =
      high_resolution_clock::now() - high_resolution_clock::duration<double>(init);
}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Start counting time
 * @param init Initial number of seconds for the stopwatch
 */
void Stopwatch::Start(double init)
{

}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Stop counting time
 * @return Elapsed seconds
 */
double Stopwatch::Stop()
{

}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Take a split
 * @return Number of seconds since the last split, or since the stopwatch was
 * started if this is the first split
 */
double Stopwatch::Split()
{

}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Restart the stop watch
 * @param init Number of seconds to restart at
 * @return The number of seconds that had elapsed before the timer was
 * restarted
 */
double Stopwatch::Reset(double init )
{

}

//////////////////////////////////////////////////////////////////////////////

/**
 * @brief Get the current number of seconds that have elapsed since the timer
 * was started
 * @return
 */
double Stopwatch::Time()
{

}

//////////////////////////////////////////////////////////////////////////////

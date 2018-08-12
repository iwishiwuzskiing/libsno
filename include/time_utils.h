/**
 * @brief Function related to time and timing
 */

#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>
#include <stddef.h>
namespace so
{
namespace Time_utils
{
/**
 * @brief Return the current unix time in decimal seconds
 * @return Time since 00:00 on Jan 1 1970
 * @throws If the number of microseconds since the UNIX epoch cannot be stored
 * in a double
 */
double Unix_time();

} // namespace Time_utils
} // namespace so

#endif

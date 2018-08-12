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
 */
static double Unix_time();

}
}

#endif

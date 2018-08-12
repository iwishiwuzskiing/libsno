#include <boost/numeric/conversion/cast.hpp>
#include <time_utils.h>
#include <so_exception.h>

double so::Time_utils::Unix_time()
{
  using namespace std::chrono;
  auto unix_timestamp = std::chrono::seconds(std::time(nullptr));
  ssize_t unix_us = std::chrono::microseconds(unix_timestamp).count();
  double sec = 0;
  try
  {
    sec = boost::numeric_cast<double>(unix_us) / 1.0e6;
  }catch(const boost::bad_numeric_cast& e)
  {
    throw so::runtime_error(e.what());
  }
  return sec;
}

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

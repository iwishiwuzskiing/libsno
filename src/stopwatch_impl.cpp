
#include <boost/numeric/conversion/cast.hpp>

#include <sno/so_exception.h>
#include <stopwatch_impl.h>
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

Stopwatch_impl::Stopwatch_impl()
  :
    m_start_time(),
    m_last_split(m_start_time),
    m_elapsed_time(0),
    m_running(false)
{

}

//////////////////////////////////////////////////////////////////////////////

void Stopwatch_impl::Start()
{
  if(m_running)
  {
    return;
  }
  Reset();
  m_running = true;
}

//////////////////////////////////////////////////////////////////////////////

double Stopwatch_impl::Stop()
{
  update_elapsed_time();
  m_running = false;
  return m_elapsed_time;
}

//////////////////////////////////////////////////////////////////////////////

double Stopwatch_impl::Split()
{
  if(!m_running)
  {
    return 0;
  }
  std::chrono::time_point<Clock_type> now = Clock_type::now();
  auto us = std::chrono::duration_cast<std::chrono::microseconds>(now - m_last_split).count();
  m_last_split = now;
  try
  {
    double seconds = boost::numeric_cast<double>(us) / 1.0e6;
    return seconds;
  }
  catch(const boost::bad_numeric_cast& e)
  {
    throw so::runtime_error(e.what());
  }
}

//////////////////////////////////////////////////////////////////////////////

void Stopwatch_impl::Reset()
{
  m_start_time = Clock_type::now();
  m_last_split = Clock_type::now();
  m_elapsed_time = 0;
}

//////////////////////////////////////////////////////////////////////////////

double Stopwatch_impl::Get_time()
{
  update_elapsed_time();
  return m_elapsed_time;
}

//////////////////////////////////////////////////////////////////////////////

void Stopwatch_impl::update_elapsed_time()
{
  if(m_running)
  {
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(Clock_type::now() - m_start_time).count();
    try
    {
      double seconds = boost::numeric_cast<double>(us) / 1.0e6;
      m_elapsed_time = seconds;
    }
    catch(const boost::bad_numeric_cast& e)
    {
      throw so::runtime_error(e.what());
    }
  }
}

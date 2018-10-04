/**
 * \class Basic_logger Error logging class
 * Basic_logger provides a basic error logging class. The class provides error
 * logging through the stream insertion operator (<<).
 *
 */
//todo: documentations

#ifndef SO_BASIC_LOGGER_H
#define SO_BASIC_LOGGER_H

#include <string>
#include <stdio.h>
#include <fstream>

#include <boost/atomic.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/current_function.hpp>

namespace so
{

/**
 * Struct is used to define the default stream type and the functions used for
 * functors that manipulate streams *
 */
template<typename C,typename T = std::char_traits<C> >
struct Stream_info
{
  typedef std::basic_ostream<C,T>& (*StrFunc)(std::basic_ostream<C,T>&);
  static boost::shared_ptr<std::basic_ostream<C,T>> Get_default();
};

//////////////////////////////////////////////////////////////////////////////

template<typename C = char, typename T = std::char_traits<C> >
class Basic_logger
{
public:
  //Variables
  /**
   * @brief Enumerated logging levels for messages
   */
  enum Log_level
  {
    Debug     = 0xFFFFFFFFFF, ///< All Debug or higher messages
    Debug_0   = 0x01FFFFFFFF,
    Debug_1   = 0x02FFFFFFFF,
    Debug_2   = 0x04FFFFFFFF,
    Debug_3   = 0x08FFFFFFFF,
    Debug_4   = 0x10FFFFFFFF,
    Debug_5   = 0x20FFFFFFFF,
    Debug_6   = 0x40FFFFFFFF,
    Debug_7   = 0x80FFFFFFFF,

    Info      = 0x00FFFFFFFF, ///< All Info or higher messages
    Warning   = 0x0000FFFFFF, ///< All Warning or higher messages
    Severe    = 0x000000FFFF, ///< All Severe or higher messages
    Fatal     = 0x00000000FF, ///< All Fatal or higher messages
  };

  //Functions
  /**
   * @brief Errlog Log errors
   * @param scope Scope of the current error log message
   * @param level Logging level of this message
   */
  Basic_logger(const std::string scope, const Log_level level)
    :
      m_alt_stream(),
      m_msg_level(level),
      m_lock(m_mutex)
  {
    *m_out_stream << get_msg_prefix(scope);
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Errlog Log errors to a particular file, not to the "normal" log
   * location written to by m_out_stream
   * @param scope Scope of the current error log message
   * @param level Logging level of this message
   * @param file Filename to write to
   */
  Basic_logger(const std::string scope,
               const Log_level level,
               const std::string file)
    :
      m_alt_stream(new std::ofstream(file, std::ios_base::app)),
      m_msg_level(level),
      m_lock(m_mutex)
  {
    *m_alt_stream << get_msg_prefix(scope);
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * Destructor
   */
  ~Basic_logger()
  {
    //TODO: write std::endl to streams?? Just call flush()?
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Set the logging level to a particular magnitude
   * @param mag The enumerated magnitude to set the logging level to
   */
  static void Set_logging_level(const uint64_t mag)
  {
    boost::mutex::scoped_lock lock(m_mutex);
    m_logging_mask = mag;
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Set_log_file Set the log file to write to
   * @param filename Filename to write to
   */
  static void Set_log_file(std::string filename)
  {
    boost::mutex::scoped_lock lock(m_mutex);
    m_out_stream = boost::make_shared<std::ofstream>(filename,
                                                     std::ios_base::app);
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * Stream insertion operator.
   */
  template<class R>
  Basic_logger& operator<<(const R obj)
  {
    if( (m_msg_level & m_logging_mask) == m_msg_level )
    {
      if(m_alt_stream)
      {
        *m_alt_stream << obj;
      }
      else if(m_out_stream)
      {
        *m_out_stream << obj;
      }
    }
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////

  /**
   * Stream insertion operator.
   */
  Basic_logger& operator<<(typename Stream_info<C,T>::StrFunc func)
  {
    if( (m_msg_level & m_logging_mask) == m_msg_level )
    {
      if(m_alt_stream)
      {
        func(*m_alt_stream);
      }
      else if(m_out_stream)
      {
        func(*m_out_stream);
      }
    }
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////

private:
  //Variables
  /**
   * @brief m_mutex
   */
  static boost::mutex m_mutex;

  /**
   * @briefm_loggin_mask  Error logging level mask
   */
  static uint64_t m_logging_mask;

  /**
   * @brief m_out_stream Main stream for error logging. Defaults to std::cout
   * or std::wcout, but can be set to a file
   * Implemented as a shared pointer so that a new stream can be created when
   * users call Set_log_file()
   */
  static boost::shared_ptr<std::basic_ostream<C,T> > m_out_stream;

  /**
   * @brief m_local_stream Alternate stream for writing to a particular file
   * Implemented as a shared pointer because a null alternate stream indicates
   * the default should be used
   */
  boost::shared_ptr<std::basic_ostream<C,T> > m_alt_stream;

  /**
   * @brief m_msg_level Logging level of the current message
   */
  uint64_t m_msg_level;

  /**
   * @brief m_lock Scoped lock, locked when Errlog is instantiated
   */
  boost::unique_lock<boost::mutex> m_lock;

  //Functions

  /**
   * @brief get_msg_prefix Get the start of the log message. The message prefix
   *  takes the form 'LEVEL--[class::function] '
   * @param curr_func Current function string
   * @return String representing the prefix for this log message
   */
  std::string get_msg_prefix(std::string curr_func)
  {
    std::string err_prefix;
    //Write the logging level
    if(m_logging_mask >= 0x0100000000)
    {
      err_prefix = "DEBUG--";
    }
    else if(m_logging_mask >= 0x0001000000)
    {
      err_prefix = "INFO--";
    }
    else if(m_logging_mask >= 0x0000010000)
    {
      err_prefix = "WARNING--";
    }
    else if(m_logging_mask >= 0x0000000100)
    {
      err_prefix = "SEVERE--";
    }
    else //if(m_logging_mask >= 0x0000000001)
    {
      err_prefix = "FATAL--";
    }

    //Get the scope
    size_t args_start = curr_func.find_last_of('(');
    std::string func_no_args = curr_func.substr(0,args_start);
    size_t scope_start = func_no_args.find_last_of(' ') + 1;
    std::string func = func_no_args.substr(scope_start);
    err_prefix = err_prefix + "[" + func + "] ";

    return err_prefix;
  }
};

//////////////////////////////////////////////////////////////////////////////
// Typedefs for common types of error loggers
typedef Basic_logger<wchar_t> WLogger;
typedef Basic_logger<char> Logger;

} // namespace so

//////////////////////////////////////////////////////////////////////////////
// Initialize static members

template<typename C, typename T>
boost::mutex so::Basic_logger<C, T>::m_mutex;


template<typename C, typename T>
uint64_t so::Basic_logger<C ,T>::m_logging_mask(Basic_logger<C,T>::Debug);

template<typename C,typename T>
boost::shared_ptr<std::basic_ostream<C,T> > so::Basic_logger<C,T>::m_out_stream(so::Stream_info<C,T>::Get_default());

//////////////////////////////////////////////////////////////////////////////
//Macros to automatically insert scope
#define Log_msg(...) Logger(BOOST_CURRENT_FUNCTION,__VA_ARGS__)
#define Log_wmsg(...) WLogger(BOOST_CURRENT_FUNCTION,__VA_ARGS__)

//////////////////////////////////////////////////////////////////////////////


#endif

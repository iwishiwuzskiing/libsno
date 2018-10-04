#ifndef SO_EXCEPTION_H
#define SO_EXCEPTION_H

#include <exception>
#include <stdexcept>
#include <sstream>


namespace so
{

class Exception : public std::runtime_error
{
public:
  Exception() = delete;

  template<class... T>
  explicit Exception(const T&... what_args)
    :
      std::runtime_error(make_what(what_args...))
  {

  }

private:
  template<class U>
  /**
   * @brief Base case for recursively unpacking the arguments passed to
   * constructor. Converts a single argument to a string using a stringstream
   * @param arg
   * @return
   */
  void what_helper(std::stringstream& ss, const U& arg)
  {
    ss << arg;
  }


  template<class U, class... T>
  void what_helper(std::stringstream& ss,
                          const U& arg,
                          const T&... args)
  {
    what_helper(ss, arg);
    what_helper(ss, args...);
  }

  template<class... T>
  std::string make_what(const T&... what_args)
  {
    std::stringstream ss;
    what_helper(ss, what_args...);
    return ss.str();
  }
};


class Invalid_argument : public so::Exception
{
public:
  template<class... T>
  explicit Invalid_argument(const T&... what_args)
    : so::Exception(what_args...)
  {

  }
};

class Read_error : public so::Exception
{
public:
  template<class... T>
  explicit Read_error(const T&... what_args)
    : so::Exception(what_args...)
  {

  }
};

class Write_error : public so::Exception
{
public:
  template<class... T>
  explicit Write_error(const T&... what_args)
    : so::Exception(what_args...)
  {

  }
};



} // namespace so

#endif

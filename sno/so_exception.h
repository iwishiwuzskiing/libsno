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
  /**
   * @brief Default constructor, deleted
   */
  Exception() = delete;

  /**
   * @brief Constructor. A new exception with a message created by inserting the
   * arguments into a stringstream. Objects will be inserted into the
   * stringstream in the order they are argued.
   * @param what_args Objects to insert into a stringstream to create the error
   * message for this exception
   */
  template<class... T>
  explicit Exception(const T&... what_args)
    :
      std::runtime_error(make_what(what_args...))
  {

  }

private:
  /**
   * @brief Base case for recursively unpacking the arguments passed to
   * constructor. Inserts a single argument to the stringstream.
   * @param ss Stringstream to insert into to
   * @param arg Object to insert into the stringstream
   */
  template<class U>
  void what_helper(std::ostringstream& ss, const U& arg)
  {
    ss << arg;
  }


  /**
   * @brief Helper function for adding a set of arguments to a stringstream
   * @param ss Stringstream to insert into
   * @param arg Object to insert into the stringstream first
   * @param args Subsequent objects to insert into the stringstream
   */
  template<class U, class... T>
  void what_helper(std::ostringstream& ss,
                   const U& arg,
                   const T&... args)
  {
    what_helper(ss, arg);
    what_helper(ss, args...);
  }

  /**
   * @brief Helper function for creating the what() message for the exception.
   * Creates the exception's message by inserting the argued values into a
   * std::stringstream in the order they are argued
   * @param what_args Arguments to insert into the stringstream
   * @return Exception what() message
   */
  template<class... T>
  std::string make_what(const T&... what_args)
  {
    std::ostringstream ss;
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

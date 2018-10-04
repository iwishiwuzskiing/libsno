#include <sno/logger.h>

namespace
{

/**
 * @brief The null_deleter struct is used as a no-op deleter for
 * boost::shared_ptrs to statically allocated objects
 */
struct null_deleter
{
  void operator()(void const *) const
  {
  }
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////

namespace so
{

/**
 * Define the default output streams
 */
template<>
boost::shared_ptr<std::ostream> so::Stream_info<char, std::char_traits<char> >::Get_default()
{
  return boost::shared_ptr<std::ostream>(&std::cout, null_deleter());
}

template<>
boost::shared_ptr<std::wostream> so::Stream_info<wchar_t, std::char_traits<wchar_t> >::Get_default()
{
  return boost::shared_ptr<std::wostream>(&std::wcout, null_deleter());
}

}

//////////////////////////////////////////////////////////////////////////////


#include <logger.h>

////////////////////////////////////////////////////////////////////////////////
/**
 * Define the default output streams
 */
template<>
std::ostream&  stream_info<char,std::char_traits<char> >::Get_default()
{
  return std::cout;
}

template<>
std::wostream& stream_info<wchar_t,std::char_traits<wchar_t> >::Get_default()
{
  return std::wcout;
}

//////////////////////////////////////////////////////////////////////////////


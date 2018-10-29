#ifndef SO_PYTHON_UTILS_H
#define SO_PYTHON_UTILS_H

#include <string>
#include <sno/python/python_object.h>

namespace so
{
namespace Python_utils
{

/**
 * @brief Import a module
 * @param name Name of the module to import
 * @return Python_object containing the loaded module
 * @throws so::Read_error if the module can't be loaded
 */
so::Python_object Import_module(const std::string name);

/**
 * @brief Make a python tuple from a set of values
 * @param types Values to make tuple from
 * @return Python object containing the tuple
 * @throws Any exceptions that may be thrown by converting any of the T types
 * to python objects
 */
template<class ...T>
so::Python_object Make_pytuple(T...types)
{
  return so::Python_object(std::make_tuple(types...));
}

} // namespace Python_utils
} // namespace so
#endif

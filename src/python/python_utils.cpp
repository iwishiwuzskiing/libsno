#include <sno/python/python_utils.h>


////////////////////////////////////////////////////////////////////////////////

so::Python_object so::Python_utils::Import_module(const std::string name)
{
  so::Python_object module(PyImport_ImportModule(name.c_str()), false);
  if(!module.Get())
  {
    throw so::Read_error("Failed to load module '" + name + "'");
  }
  return module;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

/**
 * @class Python_interpreter
 * Wrapper class around the Python interpreter for the python C api
 */

#ifndef SO_PYTHON_INTERPRETER_IMPL_H
#define SO_PYTHON_INTERPRETER_IMPL_H

#include <string>
#include <Python.h>

namespace so
{
class Python_interpreter_impl
{
public:
  Python_interpreter_impl(const std::string python_program = "")
    :
      m_program_name(nullptr)
  {
    if(!python_program.empty())
    {
      size_t len;
      m_program_name = Py_DecodeLocale(python_program.c_str(), &len);
      Py_SetProgramName(m_program_name);
    }
    Py_Initialize();
    PySys_SetArgvEx(0, nullptr, 0);
  }

  ~Python_interpreter_impl()
  {
    Py_Finalize();
    PyMem_RawFree(m_program_name);
  }

private:
  /**
   * @brief m_program_name The path to the python executable to invoke for
   * interpretation
   */
  wchar_t* m_program_name;
};
}

#endif

/**
 * @class Python_interpreter
 * Wrapper class around the Python interpreter for the python C api
 */

#ifndef SO_PYTHON_INTERPRETER_H
#define SO_PYTHON_INTERPRETER_H

#include <memory>

namespace so
{
class Python_interpreter_impl;

class Python_interpreter
{
public:
  /**
   * @brief Constructor, a new python interpreter using the specified python
   * program
   * @param python_program Name of the python executable to use. Can be omitted
   * to use the system default python
   */
  Python_interpreter(const std::string python_program = "");

  /**
   * Destructor
   */
  ~Python_interpreter();


  // There can only be a single python interpreter, so delete the copy/
  // move constructors and assignment operators
  Python_interpreter(const Python_interpreter& other) = delete;
  Python_interpreter(const Python_interpreter&& other) = delete;
  Python_interpreter& operator=(Python_interpreter other) = delete;
  Python_interpreter& operator=(const Python_interpreter&& other) = delete;

private:
  /**
   * @brief Implementation object for the interpreter
   */
  std::unique_ptr<Python_interpreter_impl> m_pimpl;
};
}

#endif

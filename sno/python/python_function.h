#ifndef SO_PYTHON_FUNCTION_H
#define SO_PYTHON_FUNCTION_H

#include <vector>
#include <sno/python/python_object.h>
#include <sno/so_exception.h>
#include <sno/python/python_utils.h>

namespace so
{
template <class R_type, class... Args>
class Python_function
{
public:
  /**
   * @brief Constructor. A new python function with the specified name from the
   * provided module
   * @param module Module the function is from
   * @param name Name of the function
   */
  Python_function(so::Python_object module, std::string name)
    :
      m_func(nullptr)
  {
    // Check if module is valid
    if(!PyModule_Check(module.Get()))
    {
      throw(so::Invalid_argument(name, "Invalid module"));
    }
    
    // Get function from module
    m_func = PyObject_GetAttrString(module.Get(), name.c_str());
    
    //
    if(!m_func || !PyCallable_Check(m_func))
    {
      std::string module_name = so::Python_object(PyModule_GetFilename(module.Get())).As<std::string>();
      throw(so::Invalid_argument(name, " is not a valid python function"));
    }
  }

  /**
   * @brief Destructor
   */
  ~Python_function()
  {
    Py_XDECREF(m_func);
  }

  /**
   * @brief Call the function
   * @param args Arguments passed to the function
   * @return output of the function
   */
  R_type operator()(Args... args)
  {
    // Unpack params into arg_tuple
    so::Python_object arg_tuple = so::Python_utils::Make_pytuple(args...);

    PyObject* out = PyObject_CallObject(m_func, arg_tuple.Get());
    if(!out)
    {
      //TODO: throw? What will out be for a function that doesn't return anything
    }

    // Convert the returned object to the output type.
    // PyObject_CallObject returns a new reference. The temporary Python_object
    // created here will take ownership of that reference, then decrement the
    // reference count when the function ends.
    return so::Python_object(out, false).As<R_type>();
  }

private:
  /**
   * @brief m_func The stored function
   */
  PyObject* m_func;

};
}
#endif

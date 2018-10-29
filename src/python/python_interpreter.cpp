#include <python/python_interpreter_impl.h>
#include <sno/python/python_interpreter.h>


//////////////////////////////////////////////////////////////////////////////

so::Python_interpreter::Python_interpreter(const std::string python_program)
  :
    m_pimpl(new Python_interpreter_impl(python_program))
{

}

//////////////////////////////////////////////////////////////////////////////

// std::unique_ptr<T> has undefined behavior if it's destructor is called from
// a place in the code where T has incomplete type. The default compiler
// generated destructor for this class would result in that happening, so
// the destructor has to get explicitly defined here, where
// Python_interpreter_impl has been defined
so::Python_interpreter::~Python_interpreter()
{

}


//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

#ifndef SO_PYTHON_OBJECT_H
#define SO_PYTHON_OBJECT_H
#include <string>
#include <Python.h>
#include <sno/so_exception.h>
#include <tuple>
#include <vector>

namespace so
{
/**
 * @brief The Python_object class wraps a pointer to a PyObject.
 * The class will automatically decrement the pointer's reference count when
 * it is destructed.
 * The class provides a number of convenience functions to convert between
 * C++ data types and PyObjects
 *
 * @note This class wraps a pointer, copy and assignment operations will
 * therefore always be shallow operations.
 *
 */
class Python_object
{
public:
  // Delete default constructor
  Python_object() = delete;

  /**
   * @brief Constructor, a wrapper around the provided python object
   * The class will automatically decrement the pointer's reference count when
   * it is destructed. As such, if the class is constructed by copying a
   * borrowed reference the reference count must be incremented at construction.
   * If obj is a new reference the reference count should not be incremented
   * @param obj Python object to wrap
   * @param incref True if the reference count for this object should be
   * increased. This class will always decrement the reference count when
   * destructed, so the reference count should be increased if this
   * Python_object is being initialized with a borrowed reference. If obj is a
   * new reference then the reference count should not be incremented
   */
  Python_object(PyObject* obj, bool incref)
    :
      m_obj(obj)
  {
    if(incref)
    {
      Py_XINCREF(m_obj);
    }
  }

  /**
   * @brief Constructor, a new python object representing the specified string
   * @param str String to store in a python object
   */
  Python_object(const std::string str)
    :
      m_obj(PyBytes_FromString(str.c_str()))
  {
    // PyBytes_FromString returns a new reference, so there's no need to
    // increment reference count
    if(!m_obj)
    {
      throw so::Invalid_argument("Failed to create PyBytes from '" + str + "'");
    }
  }

  /**
   * @brief Constructor, a new python tuple from the C++ tuple
   * @param tuple Tuple to convert to a python tuple
   */
  template<class...Types>
  Python_object(const std::tuple<Types...> tuple)
    :
      m_obj(PyTuple_New(sizeof... (Types)))
  {
    // PyTuple_New returns a new reference, so there's no need to increment
    // reference count
    if(!m_obj)
    {
      throw so::Invalid_argument("Failed to create PyTuple");
    }
    make_pytuple(tuple, m_obj);
  }

  /**
   * @brief Copy constructor. A new Python object storing the same object
   * (i.e. a shallow copy) of the other python object
   * @param other
   */
  Python_object(const Python_object& other)
  {
    // Remove any previously held references
    Py_XDECREF(m_obj);

    // Get a copy of the other object's internal PyObject
    m_obj = other.m_obj;

    // Increase the reference count
    Py_XINCREF(m_obj);
  }

  //TODO: are these move semantics correct?
  Python_object(Python_object&& other)
  {
    swap(*this, other);
  }

  /**
   * @brief Assignment operator. Creates a shallow copy of other
   * @param other Python object to copy
   * @return Python object that is a shallow copy of other
   */
  Python_object& operator=(Python_object other)
  {
    swap(*this, other);
    return *this;
  }


  /**
   * Destructor, decrements the reference count
   */
  ~Python_object()
  {
    Py_XDECREF(m_obj);
  }

  /**
   * @brief Get the raw PyObject that is being managed
   * @return Raw python object being managed
   */
  PyObject* Get()
  {
    return m_obj;
  }

  /**
   * @brief Get the value of this python object as the specified type
   * @return Python object as the specified type
   * @throws so::runtime_error if this object cannot be converted to T
   */
  template<class T>
  T As() const
  {
    T out;
    get_as(out);
    return out;
  }

private:
  /**
   * @brief m_obj The python object managed by this class
   */
  PyObject* m_obj;

  /**
   * @brief Swap the contents of two Python_objects.
   * @param[in,out] first First object, whose contents should be swapped with second
   * @param[in,out] second Second object whose contents should be swapped with first
   */
  friend void swap(Python_object& first, Python_object& second) // nothrow
  {
    // enable ADL
    using std::swap;

    // Swap. Assume that reference counts were correct beforehand, thus no need
    // to modify reference counts when swapping
    swap(first.m_obj, second.m_obj);
  }

  /**
   * @brief Base case for populating py_tuple, does nothing
   */
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I == sizeof...(Tp), void>::type
  make_pytuple(const std::tuple<Tp...>&, PyObject*)
  { }

  /**
   * @brief Populate a python tuple from a std::tuple
   * @param[in] t C++ tuple to populate python tuple from
   * @param[out] py_tuple Python tuple to be populated
   */
  template<std::size_t I = 0, typename... Tp>
  inline typename std::enable_if<I < sizeof...(Tp), void>::type
  make_pytuple(const std::tuple<Tp...>& t, PyObject* py_tuple)
  {
    PyTuple_SetItem(py_tuple, I, so::Python_object(std::get<I>(t)).Get());
    make_pytuple<I + 1, Tp...>(t, py_tuple);
  }

  /**
   * @brief Trivial conversion for the As() function. Get this object as a
   * Python object.
   * @param[out] obj Object as a Python object
   */
  void get_as(Python_object& obj) const;

  /**
   * @brief Get this object as a double
   * @param[out] dbl Object as a double
   * @throws so::Invalid_argument if this object cannot be represented as a
   * double
   */
  void get_as(double& dbl) const;

  /**
   * @brief Get this object as a string, as with the repr() function in python
   * @param[out] str String representing this object
   * @throws so::Invalid_argument if this object cannot be represented as a string
   */
  void get_as(std::string& str) const;

  /**
   * @brief Get this object as a vector.
   * Strong exception guarantee.
   * @param[out] vec Vector to populate
   * @throws so::Invalid_argument if this object cannot be converted into the
   * specified type of vector.
   * @throws Any exceptions that may be thrown by converting T to a python
   * object
   */
  template<class T>
  void get_as(std::vector<T>& vec) const
  {
    if(!PySequence_Check(m_obj))
    {
      throw so::Invalid_argument("Object is not a sequence");
    }

    // Populate a temporary object in case creation fails
    std::vector<T> out_tmp;
    Py_ssize_t num = PySequence_Size(m_obj);
    for(ssize_t k = 0; k < num; k++)
    {
      out_tmp.push_back(so::Python_object(PySequence_GetItem(m_obj, k), false).As<T>());
    }
    std::swap(vec, out_tmp);
  }
};
}
#endif

#ifndef NJOY_SCION_PYTHON_DEFINITIONS
#define NJOY_SCION_PYTHON_DEFINITIONS

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

/**
 *  @brief Add standard domain definitions
 *
 *  This adds the following standard functions:
 *    in_inside, is_contained
 *
 *  @param[in] component   the domain to which the definitions have to be added
 */
template < typename Component, typename PythonClass >
void addStandardDomainDefinitions( PythonClass& component ) {

  component
  .def(

    "is_inside",
    &Component::isInside,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  )
  .def(

    "is_contained",
    &Component::isContained,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  );
}

#endif

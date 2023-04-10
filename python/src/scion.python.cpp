// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapMathModule( python::module& );

/**
 *  @brief scion python bindings
 *
 *  The name given here (scion) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( scion, module ) {

  // wrap the math submodule
  wrapMathModule( module );
}

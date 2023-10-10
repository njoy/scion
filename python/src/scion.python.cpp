// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations
void wrapInterpolationModule( python::module& );
void wrapIntegrationModule( python::module& );
void wrapLinearisationModule( python::module& );
void wrapMathModule( python::module& );

/**
 *  @brief scion python bindings
 *
 *  The name given here (scion) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( scion, module ) {

  // wrap the interpolation submodule
  wrapInterpolationModule( module );

  // wrap the integration submodule
  wrapIntegrationModule( module );

  // wrap the linearisation submodule
  wrapLinearisationModule( module );

  // wrap the math submodule
  wrapMathModule( module );
}

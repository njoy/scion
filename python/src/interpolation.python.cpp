// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace interpolation {

  // interpolation functions
  void wrapInterpolationFunctions( python::module& );
}

void wrapInterpolationModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "interpolation",
    "Common interpolation capabilities and components"
  );

  // wrap scion's math capabilities
  interpolation::wrapInterpolationFunctions( submodule );
}

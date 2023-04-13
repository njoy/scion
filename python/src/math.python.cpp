// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace math {

  // evaluation schemes
  void wrapHorner( python::module& );

  // special functions
  void wrapLegendre( python::module& );

  // function interface
  void wrapIntervalDomain( python::module& );
  void wrapOpenDomain( python::module& );
}

void wrapMathModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "math",
    "Common math capabilities and components"
  );

  // wrap scion's math capabilities
  math::wrapHorner( submodule );
  math::wrapLegendre( submodule );
  math::wrapIntervalDomain( submodule );
  math::wrapOpenDomain( submodule );
}

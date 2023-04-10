// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace math {

  void wrapHorner( python::module& );
}

void wrapMathModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "math",
    "Common math components"
  );

  // wrap scion's math capabilities
  math::wrapHorner( submodule );
}

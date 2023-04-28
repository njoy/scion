// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace linearisation {

  // linearisation functors
  void wrapMidpointSplit( python::module& );
  void wrapToleranceConvergence( python::module& );
  void wrapLineariser( python::module& );
}

void wrapLinearisationModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "linearisation",
    "Common linearisation capabilities and components"
  );

  // wrap scion's linearisation capabilities
  linearisation::wrapMidpointSplit( submodule );
  linearisation::wrapToleranceConvergence( submodule );
  linearisation::wrapLineariser( submodule );
}

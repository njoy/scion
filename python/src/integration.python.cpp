// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

// declarations
namespace integration {

  // integration functions
  void wrapIntegrationFunctions( python::module& );
  void wrapGaussLegendre( python::module& );
  void wrapGaussLobatto( python::module& );
}

void wrapIntegrationModule( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "integration",
    "Common integration capabilities and components"
  );

  // wrap scion's integration capabilities
  integration::wrapIntegrationFunctions( submodule );
  integration::wrapGaussLegendre( submodule );
  integration::wrapGaussLobatto( submodule );
}

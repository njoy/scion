// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// local includes
#include "scion/integration/GaussLobatto.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace integration {

template < int N, typename X, typename Y = X >
void wrapGaussLobattoFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::integration::GaussLobatto< N, X, Y >;

  // wrap views created by this component

  // create the component
  std::string description = "Gauss-Lobatto " + std::to_string( N ) +
                            "-point quadrature rule";
  python::class_< Component > component(

    module,
    name.c_str(),
    description.c_str()
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the quadrature rule"
  );

  // add standard quadrature definitions
  addStandardQuadratureDefinitions< Component, X, Y >( component );
}

void wrapGaussLobatto( python::module& module ) {

  // wrap the integration functions we need
  wrapGaussLobattoFor<  2, double >( module, "GaussLobatto2" );
  wrapGaussLobattoFor<  4, double >( module, "GaussLobatto4" );
  wrapGaussLobattoFor<  6, double >( module, "GaussLobatto6" );
  wrapGaussLobattoFor<  8, double >( module, "GaussLobatto8" );
  wrapGaussLobattoFor< 10, double >( module, "GaussLobatto10" );
  wrapGaussLobattoFor< 16, double >( module, "GaussLobatto16" );
  wrapGaussLobattoFor< 32, double >( module, "GaussLobatto32" );
  wrapGaussLobattoFor< 64, double >( module, "GaussLobatto64" );
}

} // namespace integration

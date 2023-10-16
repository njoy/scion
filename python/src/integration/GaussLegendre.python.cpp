// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// local includes
#include "scion/integration/GaussLegendre.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace integration {

template < int N, typename X, typename Y = X >
void wrapGaussLegendreFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::integration::GaussLegendre< N, X, Y >;

  // wrap views created by this component

  // create the component
  std::string description = "Gauss-Legendre " + std::to_string( N ) +
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

void wrapGaussLegendre( python::module& module ) {

  // wrap the integration functions we need
  wrapGaussLegendreFor<  2, double >( module, "GaussLegendre2" );
  wrapGaussLegendreFor<  4, double >( module, "GaussLegendre4" );
  wrapGaussLegendreFor<  6, double >( module, "GaussLegendre6" );
  wrapGaussLegendreFor<  7, double >( module, "GaussLegendre7" );
  wrapGaussLegendreFor<  8, double >( module, "GaussLegendre8" );
  wrapGaussLegendreFor< 10, double >( module, "GaussLegendre10" );
}

} // namespace integration

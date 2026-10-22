// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/CoulombPenetrabilityTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapCoulombPenetrabilityTableFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::CoulombPenetrabilityTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Tabulated data with Coulomb penetrability interpolation "
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X >, std::vector< Y >, X >(),
    python::arg( "x" ), python::arg( "y" ), python::arg( "t") = 0.0,
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the x values of the tabulated data\n"
    "    y      the y values of the tabulated data\n"
    "    t      the threshold value, default = 0.0"
  ).def_property_readonly(

    "threshold",
    &Component::threshold,
    "The reaction threshold"
  );

  // add standard function definitions
  addStandardSingleInterpolationTableDefinitions< Component, X, Y >( component );
}

void wrapCoulombPenetrabilityTable( python::module& module ) {

  wrapCoulombPenetrabilityTableFor< double >( module, "CoulombPenetrabilityTable" );
}

} // namespace math

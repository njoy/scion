// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/LegendreSeries.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapLegendreSeriesFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::LegendreSeries< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A Legendre series function y -> f(x) = sum c_i P_i(x) of order n\n\n"
    "This class represents a Legendre series function y -> f(x) = sum c_i P_i(x)\n"
    "defined over the domain [-1,1]. An exception is thrown for values outside\n"
    "of the domain."
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X > >(),
    python::arg( "coefficients" ),
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    coefficients   the coefficients of the Legendre series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The Legendre coefficients"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The Legendre order"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapLegendreSeries( python::module& module ) {

  wrapLegendreSeriesFor< double >( module, "LegendreSeries" );
}

} // namespace math

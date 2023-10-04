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
    "defined over the domain [-1,1].\n\n"
    "The Clenshaw recursion scheme is used for the evaluation of the series\n"
    "using the following recursion relation for Legendre polynomials:\n"
    "  P_(n+1) = (2n+1)/(n+1) x P_n - n/(n+1) P_(n-1)\n\n"
    "The derivative function of a Legendre series function is another\n"
    "Legendre series function. The coefficients of the new Legendre series\n"
    "are calculated using the derivative of a Legendre polynomial as a\n"
    "function of other Legendre polynomials:\n"
    "  d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...\n"
    "knowing that:\n"
    "  d/dx P_0 = 0.0\n"
    "  d/dx P_1 = P_0\n\n"
    "This formula can be derived using the following property of Legendre\n"
    "polynomials:\n"
    "  ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)\n\n"
    "The primitive or antiderivative of a Legendre series function is another\n"
    "Legendre series function. The coefficients of the new Legendre series\n"
    "are calculated using the integral of a Legendre polynomial as a\n"
    "function of other Legendre polynomials:\n"
    "  int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)\n\n"
    "The integrated series is defined so that the integral function for x = left\n"
    "equals 0.\n\n"
    "The derivative and primitive function is defined over the same domain as\n"
    "the original function."
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
  );

  // add standard function definitions
  addStandardSeriesDefinitions< Component, X, Y >( component );
}

void wrapLegendreSeries( python::module& module ) {

  wrapLegendreSeriesFor< double >( module, "LegendreSeries" );
}

} // namespace math

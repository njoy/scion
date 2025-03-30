// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/ChebyshevSeries.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapChebyshevSeriesFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::ChebyshevSeries< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A Chebyshev series function y -> f(x) = sum c_i T_i(x) of order n\n\n"
    "This class represents a Chebyshev series function y -> f(x) =\n"
    "sum c_i T_i(x) defined over the domain [-1,1].\n\n"
    "The Clenshaw recursion scheme is used for the evaluation of the series\n"
    "using the following recursion relation for Chebyshev polynomials:\n"
    "  T_(n+1) = 2 x T_n - T_(n-1)\n\n"
    "The derivative function of a Chebyshev series function is another\n"
    "Chebyshev series function. The coefficients of the new Chebyshev series\n"
    "are calculated using the derivative of a Chebyshev polynomial as a\n"
    "function of other Chebyshev polynomials:\n"
    "  d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even\n"
    "  d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd\n"
    "This relation can be proven by mathematical induction.\n\n"
    "The primitive or antiderivative of a Chebyshev series function is another\n"
    "Chebyshev series function. The coefficients of the new Chebyshev series\n"
    "are calculated using the integral of a Chebyshev polynomial as a\n"
    "function of other Chebyshev polynomials:\n"
    "  2 int T_n = T_(n + 1)/(n + 1) - T_(n - 1)/(n - 1)\n\n"
    "The integrated series is defined so that the integral function for x = left\n"
    "equals 0.\n\n"
    "The derivative  and primitive function is defined over the same domain as\n"
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
    "    coefficients   the coefficients of the Chebyshev series (from\n"
    "                   lowest to highest order coefficient)"
  );

  // add standard function definitions
  addStandardSeriesDefinitions< Component, X, Y >( component );
  addStandardIntegrationDefinitions< Component, X, Y >( component );
}

void wrapChebyshevSeries( python::module& module ) {

  wrapChebyshevSeriesFor< double >( module, "ChebyshevSeries" );
}

} // namespace math

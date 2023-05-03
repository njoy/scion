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
    "  T(n+2,x) = 2 x T(n+1,x) - T(n,x)"
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
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The Chebyshev coefficients"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The Chebyshev order"
  )
  .def(

    "roots",
    &Component::roots,
    python::arg( "a" ) = X( 0. ),
    "Calculate the real roots of the Legendre series so that f(x) = a\n\n"
    "This function calculates all roots on the real axis of the Legendre series.\n\n"
    "The roots of the Legendre series are the eigenvalues of the Frobenius\n"
    "companion matrix whose elements are trivial functions of the coefficients of\n"
    "the Legendre series. The resulting roots are in the complex plane so the\n"
    "roots that are not on the real axis are filtered out. The roots on the real\n"
    "axis are then improved upon using a few iterations of the Newton-Rhapson\n"
    "method.\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    a      the value of a (default is zero)"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapChebyshevSeries( python::module& module ) {

  wrapChebyshevSeriesFor< double >( module, "ChebyshevSeries" );
}

} // namespace math

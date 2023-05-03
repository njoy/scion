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
  using ToleranceConvergence = njoy::scion::linearisation::ToleranceConvergence< X, Y >;

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
    "  P(n+2,x) = (2k+1)/(k+1) x P(n+1,x) - k/(k+1) P(n,x)"
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
  )
  .def(

    "derivative",
    &Component::derivative,
    "Return the derivative of the Legendre series"
  )
  .def(

    "primitive",
    &Component::primitive,
    "Return the primitive or antiderivative of the Legendre series"
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
  )
  .def(

    "linearise",
    [] ( const Component& self, const ToleranceConvergence& convergence )
       { return self.linearise( convergence ); },
    python::arg( "convergence" ) = ToleranceConvergence(),
    "Linearise the function and return a LinearLinearTable\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    convergence    the linearisation convergence criterion (default 0.1 %)"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapLegendreSeries( python::module& module ) {

  wrapLegendreSeriesFor< double >( module, "LegendreSeries" );
}

} // namespace math

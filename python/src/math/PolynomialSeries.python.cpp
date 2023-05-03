// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/PolynomialSeries.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapPolynomialSeriesFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::PolynomialSeries< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A polynomial function y -> f(x) = sum c_i x^i of order n\n\n"
    "This class represents a polynomial function y -> f(x) = sum c_i x^i of\n"
    "order n defined over a domain. Currently, the domain can either be the\n"
    "open domain where every value of x is allowed or the interval domain that\n"
    "restricts x to an interval [a,b]."
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X > >(),
    python::arg( "coefficients" ),
    "Initialise the function with an open domain\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    coefficients   the coefficients of the polynomial series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def(

    python::init< X, X, std::vector< X > >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "coefficients" ),
    "Initialise the function with an open domain\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    lower          the lower limit of the domain\n"
    "    upper          the upper limit of the domain\n"
    "    coefficients   the coefficients of the polynomial series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The polynomial coefficients"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The polynomial series order"
  )
  .def(

    "derivative",
    &Component::derivative,
    "Return the derivative of the polynomial series"
  )
  .def(

    "primitive",
    &Component::primitive,
    python::arg( "left" ) = X( 0. ),
    "Return the primitive or antiderivative of the polynomial series\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    left   the left bound of the integral (default = 0)"
  )
  .def(

    "roots",
    &Component::roots,
    python::arg( "a" ) = X( 0. ),
    "Calculate the real roots of the polynomial series so that f(x) = a\n\n"
    "This function calculates all roots on the real axis of the polynomial series.\n\n"
    "The roots of the polynomial series are the eigenvalues of the Frobenius\n"
    "companion matrix whose elements are trivial functions of the coefficients of\n"
    "the polynomial series. The resulting roots are in the complex plane so the\n"
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

void wrapPolynomialSeries( python::module& module ) {

  wrapPolynomialSeriesFor< double >( module, "PolynomialSeries" );
}

} // namespace math

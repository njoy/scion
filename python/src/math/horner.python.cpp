// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

// local includes
#include "scion/math/horner.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y, typename Range >
void wrapHornerFor( python::module& module ) {

  module.def(

    "horner",
    [] ( const Range& coefficients, const X& x ) -> Y
       { return njoy::scion::math::horner< X, Y, Range >( coefficients, x ); },
    python::arg( "coefficients" ), python::arg( "x" ),
    "Horner evaluation of a polynomial function for different x and y types "
    "using a list or range\n\n"
    "A polynomial is defined as a sequence of coefficients c_i so that the\n"
    "polynomial of order n is given by:\n\n"
    "  y = c_n * x^n + c_(n - 1) * x^(n - 1) + c_(n - 2) * x^(n - 2) + ...\n\n"
    "With the Horner scheme, a polynomial is evaluated as follows:\n\n"
    "  y = c_n * (x + c_(n-1) * (x + c_(n - 2) * (x + ...\n\n"
    "The main reason for using the Horner scheme is computational efficiency.\n\n"
    "Source: Numerical recipes - Third edition, p201-202\n\n"
    " Arguments:\n"
    "     coefficients   a list of coefficient values (from lowest to highest\n"
    "                    order coefficient)\n"
    "     x              the value at which the polynomial must be evaluated"
  );
}

void wrapHorner( python::module& module ) {

  // wrap the horner functions we need
  wrapHornerFor< double, double, std::vector< double > >( module );
}

} // namespace math

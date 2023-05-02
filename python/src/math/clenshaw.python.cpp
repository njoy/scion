// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <vector>

// local includes
#include "scion/math/clenshaw.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y, typename Range >
void wrapClenshawFor( python::module& module ) {

  module.def(

    "clenshaw",
    [] ( Range coefficients,
         const std::function< Y( unsigned int, const X& ) >& a,
         const std::function< Y( unsigned int, const X& ) >& b,
         const Y& f0, const Y& f1, const X& x ) -> decltype(auto)
       { return njoy::scion::math::clenshaw< X, Y, Range >( coefficients, a, b,
                                                            f0, f1, x ); },
    python::arg( "coefficients" ), python::arg( "a" ), python::arg( "b" ),
    python::arg( "f0" ), python::arg( "f1" ), python::arg( "x" ),
    "Clenshaw recursion scheme using a range\n\n"
    "The Clenshaw recursion scheme is an elegant and efficient way to\n"
    "evaluate a sum of coefficients times functions that obey a recursion\n"
    "formula (such as Legendre polynomials).\n\n"
    "Consider a function defined as follows:\n\n"
    "  y = c_n * F_n(x) + c_(n - 1) * F_(n - 1)(x) + ... + c_0 * F_0(x)\n\n"
    "with F_(k + 1)(x) = a(k, x) * F_k(x) + b(k, x) * F_(k - 1)(x)\n\n"
    "We now define the values y_k:\n\n"
    "  y_(n + 1) = y_(n + 2) = 0.0\n"
    "  y_k = a(k, x) * y_(k+1) + b(k + 1, x) * y_(k + 2) + c_k  for k = n .. 1\n\n"
    "Once we know y_2 and y_1, it can be shown that the value of y will be equal to:\n\n"
    "  y = b(1, x) * F_0(x) * y_2 + F_1(x) * y_1 + c_0 * F_0(x)\n\n"
    "Source: Numerical recipes - Third edition, p222-223\n\n"
    "The main reason for using the Clenshaw recursion scheme is computational\n"
    "efficiency.\n\n"
    "Arguments:\n"
    "    coefficients   a range of coefficient values (from lowest to\n"
    "                   highest order coefficient)\n"
    "    a              the function a(k, x)\n"
    "    b              the function b(k, x)\n"
    "    f0             the value of F_0(x)\n"
    "    f1             the value of F_1(x)\n"
    "    x              the value of X"
  ).def(

    "clenshaw_legendre",
    [] ( Range coefficients, const X& x ) -> decltype(auto)
       { return njoy::scion::math::clenshawLegendre< X, Y, Range >( coefficients, x ); },
    python::arg( "coefficients" ), python::arg( "x" ),
    "Clenshaw evaluation of a Legendre series using a range\n\n"
    "Arguments:\n"
    "    coefficients   a range of coefficient values (from lowest to\n"
    "                   highest order coefficient)\n"
    "    x              the value of X"
  );
}

void wrapClenshaw( python::module& module ) {

  // wrap the clenshaw functions we need
  wrapClenshawFor< double, double, std::vector< double > >( module );
}

} // namespace math

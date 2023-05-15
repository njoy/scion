// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// local includes
#include "scion/math/newton.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapNewtonFor( python::module& module ) {

  module.def(

    "newton",
    [] ( X estimate,
         const std::function< Y( const X& ) >& functor,
         const std::function< Y( const X& ) >& derivative,
         int iterations ) -> decltype(auto)
       { return njoy::scion::math::newton< X >( estimate, functor,
                                                derivative, iterations ); },
    python::arg( "estimate" ), python::arg( "functor" ),
    python::arg( "derivative" ), python::arg( "iterations" ) = 5,
    "Apply the Newton-Raphson method for root estimation\n\n"
    "The Newton-Raphson method is used to calculate the root of a function f(x)\n"
    "provided that an estinate of the root is given. The method works by\n"
    "iteratively calculating new estimates to the root until it converges. The\n"
    "estimate of the root in iteration n+1 is given as:\n"
    "  root(n+1) = root(n) - f(root(n)) / df/dx(root(n))\n\n"
    "By default, this method will perform at the leat the number of requested\n"
    "iterations (by default 5 iterations) if the root does not converge (as\n"
    "determined by the isClose function).\n\n"
    "Caveat: this method can break down when df/dx(root(n)) is close to zero.\n\n"
    "Arguments:\n"
    "    estimate      the estimate of the root\n"
    "    functor       the function f(x)\n"
    "    derivative    the derivative of the function f(x)\n"
    "    iterations    the number of iterations if the root does not converge\n"
    "                  (by default 5 iterations)\n"
  );
}

void wrapNewton( python::module& module ) {

  // wrap the newton functions we need
  wrapNewtonFor< double >( module );
}

} // namespace math

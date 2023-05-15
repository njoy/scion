// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/chebyshev.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapChebyshevFor( python::module& module ) {

  module.def(

    "chebyshev",
    [] ( unsigned int n, const X& x ) -> decltype(auto)
       { return njoy::scion::math::chebyshev( n, x ); },
    python::arg( "order" ), python::arg( "x" ),
    "Evaluate a Chebyshev polynomial of order n\n\n"
    "Arguments:\n"
    "    order    the degree of the Chebyshev polynomial\n"
    "    x        the value at which the polynomial must be evaluated"
  );
}

void wrapChebyshev( python::module& module ) {

  // wrap the chebyshev functions we need
  wrapChebyshevFor< double >( module );
}

} // namespace math

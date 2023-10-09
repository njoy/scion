// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/legendre.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapLegendreFor( python::module& module ) {

  module.def(

    "legendre",
    [] ( unsigned int n, const X& x ) -> decltype(auto)
       { return njoy::scion::math::legendre( n, x ); },
    python::arg( "order" ), python::arg( "x" ),
    "Evaluate a Legendre polynomial of order n\n\n"
    "Arguments:\n"
    "    order    the order of the Legendre polynomial\n"
    "    x        the value at which the polynomial must be evaluated"
  );
}

void wrapLegendre( python::module& module ) {

  // wrap the legendre functions we need
  wrapLegendreFor< double >( module );
}

} // namespace math

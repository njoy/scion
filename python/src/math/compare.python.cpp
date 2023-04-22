// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

// local includes
#include "scion/math/compare.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X >
void wrapComparisonFunctionsFor( python::module& module ) {

  module.def(

    "is_close",
    [] ( const X& a, const X& b, const X& epsilon, const X& threshold ) -> decltype(auto)
       { return njoy::scion::math::isClose< X >( a, b, epsilon, threshold ); },
    python::arg( "a" ), python::arg( "b" ),
    python::arg( "epsilon" ) = X( 100. * std::numeric_limits< double >::epsilon() ),
    python::arg( "threshold" ) = X( 100. * std::numeric_limits< double >::epsilon() ),
    "Compare two floating point numbers\n\n"
    "Arguments:\n"
    "    a           the first floating point number to compare\n"
    "    b           the second floating point number to compare\n"
    "    epsilon     the relative comparison tolerance\n"
    "    threshold   the absolute comparison tolerance"
  )
  .def(

    "is_close_to_zero",
    [] ( const X& a, const X& epsilon ) -> decltype(auto)
       { return njoy::scion::math::isCloseToZero< X >( a, epsilon ); },
    python::arg( "a" ),
    python::arg( "threshold" ) = X( 100. * std::numeric_limits< double >::epsilon() ),
    "Compare a floating point number to zero\n\n"
    "Arguments:\n"
    "    a           the floating point number to compare to zero\n"
    "    threshold   the absolute comparison tolerance"
  );
}

void wrapComparisonFunctions( python::module& module ) {

  // wrap the horner functions we need
  wrapComparisonFunctionsFor< double >( module );
}

} // namespace math

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/interpolation/Histogram.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"

// namespace aliases
namespace python = pybind11;

namespace interpolation {

template < typename X, typename Y = X >
void wrapInterpolationFunctionsFor( python::module& module ) {

  module.def(

    "histogram",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::histogram( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform histogram interpolation (y is constant in x)"
  )
  .def(

    "linlin",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::linlin( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-linear interpolation (y is linear in x)"
  )
  .def(

    "linlog",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::linlog( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-logarithmic interpolation (y is linear in ln(x))"
  )
  .def(

    "loglin",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::loglin( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-linear interpolation (ln(y) is linear in x)"
  )
  .def(

    "loglog",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::loglog( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))"
  );
}

void wrapInterpolationFunctions( python::module& module ) {

  // wrap the interpolation functions we need
  wrapInterpolationFunctionsFor< double >( module );
}

} // namespace interpolation

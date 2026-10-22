// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/interpolation/Histogram.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"
#include "scion/interpolation/CoulombPenetrability.hpp"

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
    "Perform histogram interpolation (y is constant in x)\n\n"
    "Arguments:\n"
    "    x        the value of x\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "linlin",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::linlin( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-linear interpolation (y is linear in x)\n\n"
    "Arguments:\n"
    "    x        the value of x\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "linlog",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::linlog( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-logarithmic interpolation (y is linear in ln(x))\n\n"
    "Arguments:\n"
    "    x        the value of x\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "loglin",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::loglin( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-linear interpolation (ln(y) is linear in x)\n\n"
    "Arguments:\n"
    "    x        the value of x\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "loglog",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::interpolation::loglog( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))\n\n"
    "Arguments:\n"
    "    x        the value of x\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "coulomb",
    [] ( const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight, const X& threshold ) -> decltype(auto)
       { return njoy::scion::interpolation::coulomb( x, xLeft, xRight, yLeft, yRight, threshold ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ), python::arg( "threshold" ),
    "Perform coulomb penetrability interpolation\n\n"
    "Arguments:\n"
    "    x           the value of x\n"
    "    xLeft       the left value on the x interval\n"
    "    xRight      the right value on the x interval\n"
    "    yLeft       the left value on the y interval\n"
    "    yRight      the right value on the y interval\n"
    "    threshold   the threshold value"
  );
}

void wrapInterpolationFunctions( python::module& module ) {

  // wrap the interpolation functions we need
  wrapInterpolationFunctionsFor< double >( module );
}

} // namespace interpolation

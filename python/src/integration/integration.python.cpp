// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/integration/Histogram.hpp"
#include "scion/integration/LinearLinear.hpp"
#include "scion/integration/LinearLogarithmic.hpp"
#include "scion/integration/LogarithmicLinear.hpp"
#include "scion/integration/LogarithmicLogarithmic.hpp"

// namespace aliases
namespace python = pybind11;

namespace integration {

template < typename X, typename Y = X >
void wrapIntegrationFunctionsFor( python::module& module ) {

  module.def(

    "histogram",
    [] ( const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::integration::histogram( xLeft, xRight, yLeft, yRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform histogram integration (y is constant in x)\n\n"
    "Arguments:\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "linlin",
    [] ( const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::integration::linlin( xLeft, xRight, yLeft, yRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-linear integration (y is linear in x)\n\n"
    "The integral of a panel is calculated analytically using the trapezoid rule.\n"
    "Arguments:\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "linlog",
    [] ( const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::integration::linlog( xLeft, xRight, yLeft, yRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform linear-logarithmic integration (y is linear in ln(x))\n\n"
    "The integral of a panel is calculated analytically using the following\n"
    "primitive function:\n"
    "  int ln(x) =  x ln(x) - x\n\n"
    "Since y is linear in ln(x), the panel is interpolated as:\n"
    "  y = a ln(x/x1) + y1 with a = (y2 - y1) / ln(x2/x1)\n\n"
    "The integral over the panel is then given by:\n"
    "  int[x1,x2] y dx = int[x1,x2] a ln(x/x1) dx + y1 (x2 - x1)\n\n"
    "By substituting z = x/x1 in the first term, we obtain:\n"
    "  int[x1,x2] y dx = int[1,x2/x1] a x1 ln(z) dz + y1 (x2 - x1)\n"
    "which simplifies to (using the primitive):\n"
    "  int[x1,x2] y dx = a x1 (x2/x1 (ln(x2/x1) - 1) + 1) + y1 (x2 - x1)\n\n"
    "Arguments:\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "loglin",
    [] ( const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::integration::loglin( xLeft, xRight, yLeft, yRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-linear integration (ln(y) is linear in x)\n\n"
    "The integral of a panel is calculated analytically using the following\n"
    "primitive function:\n"
    "  int exp(ax) =  exp(ax) / a\n\n"
    "Since ln(y) is linear in x, the panel is interpolated as:\n"
    "  y = exp(a (x - x1) + ln(y1)) with a = ln(y2/y1) / (x2 - x1)\n"
    "    = y1 exp(a (x - x1))\n\n"
    "The integral over the panel is then given by:\n"
    "  int[x1,x2] y dx = y1 int[x1,x2] exp(a (x - x1))\n"
    "which simplifies to (using the primitive):\n"
    "  int[x1,x2] y dx = y1 / a (exp(a (x2 - x1)) - exp(a (x1 - x1)))\n"
    "                  = y1 / a (exp(a (x2 - x1)) - 1)\n"
    "                  = y1 / a (y2 / y1 - 1)\n\n"
    "Arguments:\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  )
  .def(

    "loglog",
    [] ( const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return njoy::scion::integration::loglog( xLeft, xRight, yLeft, yRight ); },
    python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-logarithmic integration (ln(y) is linear in ln(x))\n\n"
    "Since ln(y) is linear in ln(x), the panel is interpolated as:\n"
    "  y = exp(a ln(x/x1) + ln(y1)) with a = ln(y2/y1) / ln(x2/x1)\n"
    "    = y1 (x/x1)^a\n\n"
    "The integral over the panel is then given by:\n"
    "  int[x1,x2] y dx = y1 int[x1,x2] (x/x1)^a\n"
    "which simplifies to:\n"
    "  int[x1,x2] y dx = x1 y1 / (a + 1) ((x2/x1)^(a+1) - 1)\n\n"
    "Arguments:\n"
    "    xLeft    the left value on the x interval\n"
    "    xRight   the right value on the x interval\n"
    "    yLeft    the left value on the y interval\n"
    "    yRight   the right value on the y interval"
  );
}

void wrapIntegrationFunctions( python::module& module ) {

  // wrap the integration functions we need
  wrapIntegrationFunctionsFor< double >( module );
}

} // namespace integration

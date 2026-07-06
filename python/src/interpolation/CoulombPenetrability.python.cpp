// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

#include "scion/interpolation/CoulombPenetrability.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace interpolation {

template < typename X, typename Y >
void wrapCoulombPenetrability( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::interpolation::CoulombPenetrability< X, Y >;


  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Coulomb Penetrability interpolation\n\n"
    "Parameters \n"
    "---------- \n"
    "    threshold : float \n"
    "         the threshold energy of the reaction"
  );


  // wrap the component
  component
  .def(

    python::init< X >(),
    python::arg( "threshold" ),
    ""
  )
  .def(

    "__call__",
    [] ( Component& self, const X& x, const X& xLeft, const X& xRight, const Y& yLeft, const Y& yRight ) -> decltype(auto)
       { return self( x, xLeft, xRight, yLeft, yRight ); },
    python::arg( "x" ), python::arg( "xLeft" ), python::arg( "xRight" ),
    python::arg( "yLeft" ), python::arg( "yRight" ),
    "Perform logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))\n\n"
    "Parameters\n"
    "----------\n"
    "    x : float  \n"       
    "        the value of x\n"
    "    xLeft : float  \n"       
    "        the left value on the x interval\n"
    "    xRight : float  \n"       
    "        the right value on the x interval\n"
    "    yLeft : float  \n"       
    "        the left value on the y interval\n"
    "    yRight : float  \n"       
    "        the right value on the y interval"
  );
}

void wrapCoulombPenetrability( python::module& module ) {

  // wrap the interpolation functions we need
  wrapCoulombPenetrability< double, double >( module, "CoulombPenetrability" );
}

} // namespace interpolation

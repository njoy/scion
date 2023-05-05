// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// local includes
#include "scion/math/ChebyshevApproximation.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapChebyshevApproximationFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::ChebyshevApproximation< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Approximation of a function f(x) in the [a,b] domain using a Chebyshev series"
  );

  // wrap the component
  component
  .def(

    python::init( [] ( X lower, X upper,
                       const std::function< Y(const X&) >& function,
                       unsigned int order )
                     { return Component( lower, upper, function, order ); } ),
    python::arg( "lower" ), python::arg( "upper" ), python::arg( "function" ),
    python::arg( "order" ),
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self        the function\n"
    "    lower       the lower limit of the domain\n"
    "    upper       the upper limit of the domain\n"
    "    function    the function to be approximated\n"
    "    order       the order of the approximation"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The Chebyshev coefficients"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The Chebyshev order"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapChebyshevApproximation( python::module& module ) {

  wrapChebyshevApproximationFor< double >( module, "ChebyshevApproximation" );
}

} // namespace math

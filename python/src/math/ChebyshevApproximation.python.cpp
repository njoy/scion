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
  .def(

    "derivative",
    &Component::derivative,
    "Return the derivative of the approximated function\n\n"
    "The derivative is equal to the derivative of the underlying Chebyshev series\n"
    "and is defined over the same domain as the original approximated function."

  )
  .def(

    "primitive",
    &Component::primitive,
    python::arg( "left" ) = X( 0. ),
    "Return the primitive or antiderivative of the approximated function\n\n"
    "The primitive is equal to the primitive of the underlying Chebyshev\n"
    "series and is defined over the same domain as the original approximated\n"
    "function.\n\n"
    "The integral function is defined so that the integral function for x = left\n"
    "equals 0.\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    left   the left bound of the integral (default = 0)"
  )
  .def(

    "roots",
    &Component::roots,
    python::arg( "a" ) = X( 0. ),
    "Calculate the real roots of the approximated function so that f(x) = a\n\n"
    "This function calculates all roots on the real axis of the approximated\n"
    "function as the roots of the underlying Chebyshev series.\n"
    "Arguments:\n"
    "    self   the function\n"
    "    a      the value of a (default is zero)"
  );

  // add standard function definitions
  addStandardSeriesDefinitions< Component, X, Y >( component );
}

void wrapChebyshevApproximation( python::module& module ) {

  wrapChebyshevApproximationFor< double >( module, "ChebyshevApproximation" );
}

} // namespace math

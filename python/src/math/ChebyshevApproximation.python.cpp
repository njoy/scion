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
    "Approximation of a function f(x) in the [a,b] domain using a Chebyshev series\n\n"
    "Users should note that the underlying Chebyshev series is ALWAYS defined in\n"
    "[-1, 1] and that the approximated function is defined on [a,b] and that\n"
    "a domain transformation is required to go from one to the other. This\n"
    "transformation is performed inside this object.\n\n"
    "Chebyshev function approximation only works well within the defined\n"
    "domain. Outside of the domain, the approximated function can quickly diverge.\n"
    "Range checking by the user is advised.\n\n"
    "The derivative function of an approximated function is another approximated\n"
    "function. The derivative is equal to the derivative of the underlying\n"
    "Chebyshev series and is defined over the same domain as the original\n"
    "approximated function.\n\n"
    "The primitive of an approximated function is another approximated\n"
    "function. The primitive is equal to the primitive of the underlying\n"
    "Chebyshev series and is defined over the same domain as the original\n"
    "approximated function.\n\n"
    "The integral function is defined so that the integral function for x = left\n"
    "equals 0."
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

    python::init< X, X, std::vector< Y > >(),
    python::arg( "lower" ), python::arg( "upper" ), python::arg( "coefficients" ),
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self            the function\n"
    "    lower           the lower limit of the domain\n"
    "    upper           the upper limit of the domain\n"
    "    coefficients    the coefficients that approximate the function"
  );

  // add standard function definitions
  addStandardSeriesDefinitions< Component, X, Y >( component );
}

void wrapChebyshevApproximation( python::module& module ) {

  wrapChebyshevApproximationFor< double >( module, "ChebyshevApproximation" );
}

} // namespace math

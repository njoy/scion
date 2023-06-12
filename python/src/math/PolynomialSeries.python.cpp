// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/PolynomialSeries.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapPolynomialSeriesFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::PolynomialSeries< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A polynomial function y -> f(x) = sum c_i x^i of order n\n\n"
    "This class represents a polynomial function y -> f(x) = sum c_i x^i of\n"
    "order n defined over a domain. Currently, the domain can either be the\n"
    "open domain where every value of x is allowed or the interval domain that\n"
    "restricts x to an interval [a,b]. An exception is thrown for values\n"
    "outside of the domain."
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X > >(),
    python::arg( "coefficients" ),
    "Initialise the function with an open domain\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    coefficients   the coefficients of the polynomial series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def(

    python::init< X, X, std::vector< X > >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "coefficients" ),
    "Initialise the function with an open domain\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    lower          the lower limit of the domain\n"
    "    upper          the upper limit of the domain\n"
    "    coefficients   the coefficients of the polynomial series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The polynomial coefficients"
  )
  .def_property_readonly(

    "order",
    &Component::order,
    "The polynomial series order"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapPolynomialSeries( python::module& module ) {

  wrapPolynomialSeriesFor< double >( module, "PolynomialSeries" );
}

} // namespace math

// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/IntervalDomain.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X >
void wrapIntervalDomainFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::IntervalDomain< X >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A domain for a function y -> f(x) for x inside [a,b]"
  );

  // wrap the component
  component
  .def(

    python::init< X, X >(),
    python::arg( "lower" ), python::arg( "upper" ),
    "Initialise the domain\n\n"
    "Arguments:\n"
    "    self    the domain\n"
    "    lower   the lower limit of the domain\n"
    "    upper   the upper limit of the domain"
  )
  .def_property_readonly(

    "lower_limit",
    &Component::lowerLimit,
    "The lower limit of the domain"
  )
  .def_property_readonly(

    "upper_limit",
    &Component::upperLimit,
    "The upper limit of the domain"
  )
  .def(

    "is_inside",
    &Component::isInside,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  )
  .def(

    "is_contained",
    &Component::isContained,
    python::arg( "x" ),
    "Check whether or not a value is inside the domain (including boundaries)\n\n"
    "Arguments:\n"
    "    self   the domain\n"
    "    x      the value to be tested"
  );
}

void wrapIntervalDomain( python::module& module ) {

  wrapIntervalDomainFor< double >( module, "IntervalDomain" );
}


} // namespace math

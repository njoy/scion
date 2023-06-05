// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/OpenDomain.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X >
void wrapOpenDomainFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::OpenDomain< X >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A domain for a function y -> f(x) including any value of x"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the domain\n\n"
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

void wrapOpenDomain( python::module& module ) {

  wrapOpenDomainFor< double >( module, "OpenDomain" );
}

} // namespace math

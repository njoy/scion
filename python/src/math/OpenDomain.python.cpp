// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/OpenDomain.hpp"
#include "definitions.hpp"

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
  );

  // add standard domain definitions
  addStandardDomainDefinitions< Component >( component );
}

void wrapOpenDomain( python::module& module ) {

  wrapOpenDomainFor< double >( module, "OpenDomain" );
}

} // namespace math

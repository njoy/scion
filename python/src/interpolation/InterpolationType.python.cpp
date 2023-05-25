// system includes
#include <pybind11/pybind11.h>

// local includes
#include "scion/interpolation/InterpolationType.hpp"

// namespace aliases
namespace python = pybind11;

namespace interpolation {

void wrapInterpolationType( python::module& module ) {

  // type aliases
  using Component = njoy::scion::interpolation::InterpolationType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "InterpolationType",
    "The interpolation types",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "Histogram", Component::Histogram )
  .value( "LinearLinear", Component::LinearLinear )
  .value( "LinearLog", Component::LinearLog )
  .value( "LogLinear", Component::LogLinear )
  .value( "LogLog", Component::LogLog );
}

} // namespace interpolation

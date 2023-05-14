// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/fromENDF.hpp"

// namespace aliases
namespace python = pybind11;

// declarations

void wrapEndfModule( python::module& module ) {

  module.def(

    "from_endf",
    python::overload_cast< const njoy::ENDFtk::section::Type< 1, 452 >& >( &njoy::scion::fromENDF ),
    python::arg( "section" ),
    "test load total nubar"
  )
  .def(

    "from_endf",
    python::overload_cast< const njoy::ENDFtk::section::Type< 6 >::ContinuumEnergyAngle::LegendreCoefficients& >( &njoy::scion::fromENDF ),
    python::arg( "section" ),
    "test load Legendre series"
  );
}

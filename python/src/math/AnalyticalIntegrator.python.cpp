// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/AnalyticalIntegrator.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapAnalyticalIntegratorFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::AnalyticalIntegrator< X >;
  using InterpolationTable = njoy::scion::math::InterpolationTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Analytical integration of data over a number of successive integration intervals"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X > >(),
    python::arg( "boundaries" ),
    "Initialise the integrator\n\n"
    "Arguments:\n"
    "    self         the integrator\n"
    "    boundaries    the integration interval boundaries"
  )
  .def(

    python::init< X, X >(),
    python::arg( "a" ), python::arg( "b" ),
    "Initialise the integrator\n\n"
    "Arguments:\n"
    "    self   the integrator\n"
    "    a      the lower limit of the integration interval\n"
    "    b      the upper limit of the integration interval"
  )
  .def_property_readonly(

    "boundaries",
    &Component::boundaries,
    "The boundaries"
  )
  .def_property_readonly(

    "number_intervals",
    &Component::numberIntervals,
    "The number of integration intervals"
  )
  .def(

    "integrate",
    [] ( const Component& self, const InterpolationTable& table ) ->decltype(auto)
       { return self.integrate( table ); },
    python::arg( "table" )
  );
}

void wrapAnalyticalIntegrator( python::module& module ) {

  wrapAnalyticalIntegratorFor< double >( module, "AnalyticalIntegrator" );
}

} // namespace math

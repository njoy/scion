// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/InterpolationTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapInterpolationTableFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::InterpolationTable< X, Y >;
  using InterpolationType = njoy::scion::interpolation::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Tabulated data with one or more interpolation types"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X >, std::vector< Y >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "x" ), python::arg( "y" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the function\n\n"
    "Arguments:\n"
    "    self           the function\n"
    "    x              the x values of the tabulated data\n"
    "    y              the y values of the tabulated data\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "x",
    &Component::x,
    "The x values of the table"
  )
  .def_property_readonly(

    "y",
    &Component::y,
    "The y values of the table"
  )
  .def_property_readonly(

    "boundaries",
    &Component::boundaries,
    "The boundaries of the interpolation regions"
  )
  .def_property_readonly(

    "interpolants",
    &Component::interpolants,
    "The interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "number_points",
    &Component::numberPoints,
    "The number of points in the table"
  )
  .def_property_readonly(

    "number_regions",
    &Component::numberRegions,
    "The number of interpolation regions in the table"
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapInterpolationTable( python::module& module ) {

  wrapInterpolationTableFor< double >( module, "InterpolationTable" );
}

} // namespace math

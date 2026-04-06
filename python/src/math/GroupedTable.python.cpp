// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/GroupedTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y >
void wrapGroupedTable( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::GroupedTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Table to hold grouped y values and the group boundaries.\n\n"
    "The size of the y values vector should be one less\n"
    "than the size of the group boundary values. The\n"
    "groups are assumed to be contiguous and ascending.\n\n"
    "Parameters\n"
    "----------\n"
    "    bounds : array-like \n"
    "        the boundary values\n"
    "    values : array-like\n"
    "        array of values\n"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X >, std::vector< Y > >(),
    python::arg( "bounds" ), python::arg( "values" ),
    "Create the table\n\n"
  )
  .def_property_readonly(

    "bounds",
    &Component::bounds,
    "The group boundaries"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The grouped values"
  )
  .def_property_readonly(

    "number_groups",
    &Component::numberGroups,
    "The number of groups"
  );

  addStandardEqualDefinitions< Component >( component );
  addLimitedOperatorDefinitions< Component, X, Y > ( component );

}

void wrapGroupedTable( python::module& module ) {

  wrapGroupedTable< double, double >( module, "GroupedTable" );
}

} // namespace math

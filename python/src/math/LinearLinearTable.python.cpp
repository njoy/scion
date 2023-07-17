// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/math/LinearLinearTable.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace math {

template < typename X, typename Y = X >
void wrapLinearLinearTableFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::math::LinearLinearTable< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "Tabulated data with linear-linear interpolation"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< X >, std::vector< Y > >(),
    python::arg( "x" ), python::arg( "y" ),
    "Initialise the function with an open domain\n\n"
    "Arguments:\n"
    "    self   the function\n"
    "    x      the x values of the tabulated data\n"
    "    y      the y values of the tabulated data"
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
  );

  // add standard function definitions
  addStandardFunctionDefinitions< Component, X, Y >( component );
}

void wrapLinearLinearTable( python::module& module ) {

  wrapLinearLinearTableFor< double >( module, "LinearLinearTable" );
}

} // namespace math

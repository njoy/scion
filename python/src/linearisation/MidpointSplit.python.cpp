// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/linearisation/MidpointSplit.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace linearisation {

template < typename X >
void wrapMidpointSplitFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::linearisation::MidpointSplit< X >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A split functor using a panel's midpoint"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the panel split functor"
  );

  // add standard split panel definitions
  addStandardSplitDefinitions< Component, X >( component );
}

void wrapMidpointSplit( python::module& module ) {

  wrapMidpointSplitFor< double >( module, "MidpointSplit" );
}

} // namespace linearisation

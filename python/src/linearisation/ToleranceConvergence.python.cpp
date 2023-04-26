// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace linearisation {

template < typename X, typename Y = X >
void wrapToleranceConvergenceFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = njoy::scion::linearisation::ToleranceConvergence< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A convergence functor using a single tolerance\n\n"
    "This functor class can be used to ensure convergence of the linearisation\n"
    "process using a relative tolerance and absolute difference threshold.\n"
    "With this functor, a trial value and reference value are considered\n"
    "converged if:\n"
    "  abs( trial - reference ) < ( abs( trial ) + abs( reference ) ) * tolerance\n\n"
    "For very small values (when ( abs( trial ) + abs( reference ) ) * tolerance\n"
    "is smaller than the threshold value), a trial value and reference value\n"
    "are considered converged if:\n"
    "  abs( trial - reference ) < threshold"
  );

  // wrap the component
  component
  .def(

    python::init< const Y&, const Y& >(),
    python::arg( "tolerance" ) = Y( 0.001 ),
    python::arg( "threshold" ) = Y( 1e-10 ),
    "Initialise the convergence functor\n\n"
    "Arguments:\n"
    "    self        the functor\n"
    "    tolerance   the linearisation tolerance (default 0.1 %)\n"
    "    threshold   the lowest allowed absolute difference (default 1e-10)"
  )
  .def_property_readonly(

    "tolerance",
    &Component::tolerance,
    "The linearisation tolerance"
  )
  .def_property_readonly(

    "threshold",
    &Component::threshold,
    "The linearisation threshold"
  );

  // add standard convergence definitions
  addStandardConvergenceDefinitions< Component, X, Y >( component );
}

void wrapToleranceConvergence( python::module& module ) {

  wrapToleranceConvergenceFor< double >( module, "ToleranceConvergence" );
}

} // namespace linearisation

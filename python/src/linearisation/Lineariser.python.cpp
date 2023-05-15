// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

// local includes
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/Lineariser.hpp"

// namespace aliases
namespace python = pybind11;
#include <iostream>
namespace linearisation {

// this linearisation class is here to solve an issue with the scion Lineariser.
// The scion Lineariser cannot be used on the Python side directly since it
// requires passing references from python into the C++ side - which is not
// possible. This Lineariser solve that issue by keeping the x and y arrays
// that are used in the linearisation on the C++ side of things.
template < typename X, typename Y = X >
class Lineariser {

  std::vector< X > x_;
  std::vector< Y > y_;

public:

  Lineariser() : x_(), y_() {}

  const std::vector< X >& x() const { return this->x_; }
  const std::vector< Y >& y() const { return this->y_; }

  template< typename Range, typename Functor, typename Convergence, typename Split >
  void operator()( const Range& grid, Functor&& functor,
                   Convergence&& convergence, Split&& split ) {

    this->x_.clear();
    this->y_.clear();
    njoy::scion::linearisation::Lineariser lineariser( this->x_, this->y_ );
    return lineariser( grid,
                       std::forward< Functor >( functor ),
                       std::forward< Convergence >( convergence ),
                       std::forward< Split >( split ) );
  }
};

template < typename X, typename Y = X >
void wrapLineariserFor( python::module& module, const std::string& name ) {

  // type aliases
  using Component = linearisation::Lineariser< X, Y >;
  using MidpointSplit = njoy::scion::linearisation::MidpointSplit< X, Y >;
  using ToleranceConvergence = njoy::scion::linearisation::ToleranceConvergence< X, Y >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    name.c_str(),
    "A generic linearisation object"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the lineariser"
  )
  .def_property_readonly(

    "x",
    &Component::x,
    "The x values of the linearised function"
  )
  .def_property_readonly(

    "y",
    &Component::y,
    "The y values of the linearised function"
  )
  .def(

    "__call__",
    [] ( Component& self, const std::vector< X >& grid,
         const std::function< Y( X ) >& function,
         const std::function< bool( const Y&, const Y&,
                                    const X&, const X&,
                                    const Y&, const Y& ) >& convergence,
         const std::function< X( const X&, const X&,
                                 const Y&, const Y& ) >& split )
       { return self( grid, function, convergence, split ); },
    python::arg( "grid" ), python::arg( "function" ),
    python::arg( "convergence" ), python::arg( "split" ),
    "Linearise a function\n\n"
    "    grid          the initial grid\n"
    "    functor       the function to linearise\n"
    "    convergence   the convergence criterion function\n"
    "    split         the panel splitting function"
  );
}

void wrapLineariser( python::module& module ) {

  wrapLineariserFor< double >( module, "Lineariser" );
}

} // namespace linearisation

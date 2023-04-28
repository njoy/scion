#ifndef NJOY_SCION_LINEARISATION_LINEARISER
#define NJOY_SCION_LINEARISATION_LINEARISER

// system includes
#include <functional>
#include <utility>
#include <vector>

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief A generic linearisation object
   *
   *  The Lineariser uses an initial grid to subdivide the function domain into
   *  a number of panels. It is the responsibility of the user to provide an
   *  adequate first guess of this initial grid so that the function to be
   *  linearised is either always above or below the linear interpolation over
   *  the panel. A good first guess for this initial grid would be the minima,
   *  maxima and inflection points of the function (i.e. the roots of the first
   *  and second derivative of the function).
   *
   *  During the linearisation process, a panel is subdivided into a new left
   *  and right panel using the user-provided split functor (e.g. the
   *  MidpointSplit functor that simply splits the panel in the middle). The
   *  convergence functor is then used to verify whether or not the original
   *  panel has converged (e.g. the ToleranceConvergence functor that verifies
   *  if the function value is withing a given tolerance of the interpolated
   *  value at a point). If not, linearisation continues with the right panel
   *  and the left panel is stored for later use.
   *
   *  The Lineariser uses a generic convergence test and split function. The
   *  ConvergenceBase and SplitBase classes respectively provide the interface
   *  to be implemented by functor objects to be compatible with the Lineariser.
   */
  template < typename XContainer, typename YContainer >
  class Lineariser {

    /* type aliases */
    using X = typename XContainer::value_type;
    using Y = typename XContainer::value_type;

    /* fields */
    std::reference_wrapper< XContainer > x_;
    std::reference_wrapper< YContainer > y_;
    std::vector< X > xbuffer_;
    std::vector< Y > ybuffer_;

    /* auxiliary function */
    #include "scion/linearisation/Lineariser/src/panel.hpp"

  public:

    /* constructor */
    #include "scion/linearisation/Lineariser/src/ctor.hpp"

    /* methods */
    #include "scion/linearisation/Lineariser/src/call.hpp"
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

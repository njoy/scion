#ifndef NJOY_SCION_LINEARISATION_LINEARISER
#define NJOY_SCION_LINEARISATION_LINEARISER

// system includes
#include <functional>
#include <utility>
#include <vector>

// other includes
#include "scion/interpolation/LinearLinear.hpp"

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
  template < typename XContainer, typename YContainer = XContainer >
  class Lineariser {

    /* type aliases */

    using X = typename std::decay< typename XContainer::value_type >::type;
    using Y = typename std::decay< typename YContainer::value_type >::type;

    /* fields */

    std::reference_wrapper< XContainer > x_;
    std::reference_wrapper< YContainer > y_;
    std::vector< X > xbuffer_;
    std::vector< Y > ybuffer_;

    /* auxiliary function */

    template< typename Functor, typename Convergence, typename Split >
    void panel( X xLeft, X xRight, Y yLeft, Y yRight,
            	  Functor&& functor, Convergence&& criterion, Split&& split ) {

      while ( true ) {

        const X point = split( xLeft, xRight, yLeft, yRight );
        const Y trial = interpolation::linlin( point, xLeft, xRight, yLeft, yRight );
        const Y reference = functor( point );

        if ( criterion( trial, reference, xLeft, xRight, yLeft, yRight ) ) {

          this->x_.get().push_back( xLeft );
          this->y_.get().push_back( yLeft );
          if ( ! this->xbuffer_.size() ) {

            break;
          }

          std::swap( xLeft, xRight );
          std::swap( yLeft, yRight );
          xRight = this->xbuffer_.back();
          yRight = this->ybuffer_.back();
          this->xbuffer_.pop_back();
          this->ybuffer_.pop_back();
        }
        else {

          this->xbuffer_.push_back( xRight );
          this->ybuffer_.push_back( yRight );
          xRight = point;
          yRight = reference;
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param x   a reference to the container where the x values are to be stored
     *  @param y   a reference to the container where the y values are to be stored
     */
    Lineariser( XContainer& x, YContainer& y ) :
      x_( x ), y_( y ), xbuffer_(), ybuffer_() {}

    /* methods */

    /**
     *  @brief Linearise a function
     *
     *  @param[in] first         the iterator to the beginning of the initial grid
     *  @param[in] last          the iterator to the end of the initial grid
     *  @param[in] functor       the function to linearise
     *  @param[in] convergence   the convergence criterion functor
     *  @param[in] split         the panel splitting functor
     */
    template< typename Iter, typename Functor, typename Convergence, typename Split >
    void operator()( Iter first, Iter last, Functor&& functor,
                     Convergence&& convergence, Split&& split ) {

      X xLeft = *first;
      Y yLeft = functor( xLeft );
      ++first;

      X xRight = xLeft;
      Y yRight = yLeft;

      while ( first != last ) {

        xRight = *first;
        yRight = functor( xRight );
        ++first;

        this->panel( xLeft, xRight, yLeft, yRight,
                     std::forward< Functor >( functor ),
                     std::forward< Convergence >( convergence ),
                     std::forward< Split >( split ) );

        xLeft = xRight;
        yLeft = yRight;
      }

      if ( this->x_.get().size() ) {

        this->x_.get().push_back( xRight );
        this->y_.get().push_back( yRight );
      }
    }

    /**
     *  @brief Linearise a function
     *
     *  @param[in] grid          the initial grid
     *  @param[in] functor       the function to linearise
     *  @param[in] convergence   the convergence criterion functor
     *  @param[in] split         the panel splitting functor
     */
    template< typename Range, typename Functor, typename Convergence, typename Split >
    void operator()( const Range& grid, Functor&& functor,
                     Convergence&& convergence, Split&& split ) {

      ( *this )( grid.begin(), grid.end(),
                 std::forward< Functor >( functor ),
                 std::forward< Convergence >( convergence ),
                 std::forward< Split >( split ) );
    }
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

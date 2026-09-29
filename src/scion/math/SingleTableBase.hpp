#ifndef NJOY_SCION_MATH_SINGLETABLEBASE
#define NJOY_SCION_MATH_SINGLETABLEBASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for x,y tabulated data using a single interpolation region
   *
   *  This base class provides the common interface for single region
   *  interpolation data such as the LinearLinearTable, LogLogTable, etc.
   */
  template < typename Derived, typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class SingleTableBase : public OneDimensionalFunctionBase< Derived, X, Y > {

    /* type aliases */

    using Parent = OneDimensionalFunctionBase< Derived, X, Y >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  private:

    /* fields */

    XContainer x_;
    YContainer y_;

    /* auxiliary function */

    static IntervalDomain< X >
    verifyTableAndRetrieveDomain( const XContainer& x, const YContainer& y ) {

      if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
           ( ! verification::isAtLeastOfSize( y, 2 ) ) ) {

        Log::error( "Insufficient x or y values defined for x,y tabulated data "
                    "with a single interpolation type (at least 2 points are "
                    "required)" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "y.size(): {}", y.size() );
        throw std::exception();
      }

      if ( ! verification::isSameSize( x, y ) ) {

        Log::error( "Inconsistent number of x and y values for x,y tabulated data "
                    "with a single interpolation type" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "y.size(): {}", y.size() );
        throw std::exception();
      }

      if ( ! verification::isSorted( x ) ) {

        Log::error( "The x values do not appear to be in ascending order for "
                    "x,y tabulated data with a single interpolation type" );
        throw std::exception();
      }

      if ( ! verification::isUnique( x ) ) {

        Log::error( "The x values do not appear to be unique for x,y tabulated values "
                    "with a single interpolation type" );

        auto iter = std::adjacent_find( x.begin(), x.end() );
        while ( iter != x.end() ) {

          Log::info( "Duplicate x value found: {}", *iter );
          iter = std::adjacent_find( ++iter, x.end() );
        }
        throw std::exception();
      }

      return IntervalDomain( x.front(), x.back() );
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    SingleTableBase( IntervalDomain< X >&& domain, XContainer&& x, YContainer&& y ) :
      Parent( std::move( domain ) ),
      x_( std::move( x ) ), y_( std::move( y ) ) {}

  protected:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param x   the x values of the tabulated data
     *  @param y   the y values of the tabulated data
     */
    SingleTableBase( XContainer x, YContainer y ) :
      SingleTableBase( verifyTableAndRetrieveDomain( x, y ),
                       std::move( x ), std::move( y ) ) {}

    SingleTableBase( const SingleTableBase& ) = default;
    SingleTableBase( SingleTableBase&& ) = default;

    SingleTableBase& operator=( const SingleTableBase& ) = default;
    SingleTableBase& operator=( SingleTableBase&& ) = default;

  public:

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    constexpr interpolation::InterpolationType interpolation() const noexcept {

      return static_cast< const Derived* >( this )->type();
    }

    /**
     *  @brief Return the x values of the table
     */
    const XContainer& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the y values of the table
     */
    const YContainer& y() const noexcept {

      return this->y_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      auto xIter = std::next( this->x().begin() );
      if ( x != *this->x().begin() ) {

        xIter = std::lower_bound( this->x().begin(), this->x().end(), x );
      }

      if ( this->x().end() == xIter ) {

        return Y( 0. );
      }
      else if ( this->x().begin() == xIter ) {

        return Y( 0. );
      }
      else {

        auto yIter = this->y().begin();
        std::advance( yIter, std::distance( this->x().begin(), xIter ) );

        return static_cast< const Derived* >( this )->interpolate( x, *std::prev( xIter ), *xIter,
                                                                   *std::prev( yIter ), *yIter );
      }
    }

    /**
     *  @brief Linearise the table and return the linearised x and y data
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    std::pair< std::vector< X >, std::vector< Y > >
    linearise( Convergence&& convergence = Convergence() ) const {

      std::vector< X > x;
      std::vector< Y > y;
      linearisation::Lineariser lineariser( x, y );
      lineariser( this->x(),
                  *this,
                  std::forward< Convergence >( convergence ),
                  linearisation::MidpointSplit< X, Y >() );

      return std::make_pair( std::move( x ), std::move( y ) );
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

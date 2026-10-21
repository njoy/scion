#ifndef NJOY_SCION_MATH_SINGLETABLEFUNCTIONBASE
#define NJOY_SCION_MATH_SINGLETABLEFUNCTIONBASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/math/TwoDimensionalFunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for x,f(y) tabulated data using a single interpolation region
   */
  template < typename Derived, typename X, typename F,
             typename XContainer = std::vector< X >,
             typename FContainer = std::vector< F > >
  class SingleTableFunctionBase :
      public TwoDimensionalFunctionBase< Derived, X, typename F::XType, typename F::YType > {

    /* type aliases */

    using Parent = TwoDimensionalFunctionBase< Derived, X, typename F::XType, typename F::YType >;
    using Y = typename Parent::YType;
    using Z = typename Parent::ZType;

    /* fields */

    XContainer x_;
    FContainer f_;

    /* auxiliary function */

    static void verifyTable( const XContainer& x, const FContainer& f ) {

      if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
           ( ! verification::isAtLeastOfSize( f, 2 ) ) ) {

        Log::error( "Insufficient x or f values defined for x,f(y) tabulated data "
                    "with a single interpolation type (at least 2 points are "
                    "required)" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "f.size(): {}", f.size() );
        throw std::exception();
      }

      if ( ! verification::isSameSize( x, f ) ) {

        Log::error( "Inconsistent number of x and f values for x,f(y) tabulated data "
                    "with a single interpolation type" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "f.size(): {}", f.size() );
        throw std::exception();
      }

      if ( ! verification::isSorted( x ) ) {

        Log::error( "The x values do not appear to be in ascending order for "
                    "x,f(y) tabulated data with a single interpolation type" );
        throw std::exception();
      }

      if ( ! verification::isUnique( x ) ) {

        Log::error( "The x values do not appear to be unique for x,f(y) tabulated values "
                    "with a single interpolation type" );

        auto iter = std::adjacent_find( x.begin(), x.end() );
        while ( iter != x.end() ) {

          Log::info( "Duplicate x value found: {}", *iter );
          iter = std::adjacent_find( ++iter, x.end() );
        }
        throw std::exception();
      }
    }

  protected:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param x   the x values of the tabulated data
     *  @param f   the f(y) functions of the tabulated data
     */
    SingleTableFunctionBase( XContainer x, FContainer f ) :
      x_( std::move( x ) ), f_( std::move( f ) ) {

      verifyTable( this->x(), this->f() );
    }

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
     *  @brief Return the f(y) functions of the table
     */
    const FContainer& f() const noexcept {

      return this->f_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    /**
     *  @brief Evaluate the function for a value of x and y
     *
     *  @param x   the x value to be evaluated
     *  @param y   the y value to be evaluated
     */
    Z evaluate( const X& x, const Y& y ) const {

      auto xIter = std::next( this->x().begin() );
      if ( x != *this->x().begin() ) {

        xIter = std::lower_bound( this->x().begin(), this->x().end(), x );
      }

      if ( this->x().end() == xIter ) {

        return Z( 0. );
      }
      else if ( this->x().begin() == xIter ) {

        return Z( 0. );
      }
      else {

        auto fIter = this->f().begin();
        std::advance( fIter, std::distance( this->x().begin(), xIter ) );

        return static_cast< const Derived* >( this )->interpolate( x, y, *std::prev( xIter ), *xIter,
                                                                   *std::prev( fIter ), *fIter );
      }
    }

    using Parent::operator();
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

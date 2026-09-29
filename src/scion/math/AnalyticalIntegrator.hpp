#ifndef NJOY_SCION_MATH_ANALYTICALINTEGRATOR
#define NJOY_SCION_MATH_ANALYTICALINTEGRATOR

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/math/InterpolationTable.hpp"
#include "scion/integration.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Analytical integration of tabulated data over a number of successive
   *         integration intervals
   */
  template < typename X >
  class AnalyticalIntegrator {

    /* friend declarations */

    /* fields */

    std::vector< X > boundaries_;

    /* auxiliary functions */

    static void verifyBoundaries( const std::vector< X >& boundaries ) {

      if ( ! verification::isSorted( boundaries ) ) {

        Log::error( "The integration boundary values do not appear to be sorted" );
        throw std::exception();
      }

      if ( ! verification::isUnique( boundaries ) ) {

        Log::error( "The integration boundary values do not appear to be unique" );

        auto iter = std::adjacent_find( boundaries.begin(), boundaries.end() );
        while ( iter != boundaries.end() ) {

          Log::info( "Duplicate x value found: {}", *iter );
          iter = std::adjacent_find( ++iter, boundaries.end() );
        }
        throw std::exception();
      }
    }

    template < typename Y,
               typename Interpolator,
               typename Integrator,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > integrate( const Interpolator& interpolator,
                                const Integrator& integrator,
                                const InterpolationTable< X, Y >& table ) const {

      if ( ! table.isLinearised() ) {

        Log::error( "Cannot perform analytical integration on a table that has not been linearised" );
        throw std::exception();
      }

      std::vector< I > result( this->boundaries().size() - 1, I( 0. ) );

      auto gLeft = this->boundaries().begin();
      auto gRight = std::next( gLeft );
      auto iter = result.begin();

      auto xBegin = std::lower_bound( table.x().begin(), table.x().end(), *gLeft );
      if ( xBegin == table.x().end() ) {

        return result;
      }
      auto yBegin = std::next( table.y().begin(), std::distance( table.x().begin(), xBegin ) );

      while ( gRight != this->boundaries().end() ) {

        if ( *gRight < *xBegin ) {

          if ( xBegin != table.x().begin() ) {

            *iter += integrator( *gLeft, *gRight,
                                 interpolator( *gLeft, *std::prev( xBegin ), *xBegin,
                                                       *std::prev( yBegin ), *yBegin ),
                                 interpolator( *gRight, *std::prev( xBegin ), *xBegin,
                                                        *std::prev( yBegin ), *yBegin ) );
          }
        }
        else {

          if ( ( xBegin != table.x().begin() ) && ( *gLeft < *xBegin ) ) {

            *iter += integrator( *gLeft, *xBegin,
                                 interpolator( *gLeft, *std::prev( xBegin ), *xBegin,
                                                       *std::prev( yBegin ), *yBegin ),
                                 *yBegin );
          }
          ++xBegin;
          ++yBegin;

          while ( ( xBegin != table.x().end() ) && ( *xBegin < *gRight ) ) {

            *iter += integrator( *std::prev( xBegin ), *xBegin,
                                 *std::prev( yBegin ), *yBegin );
            ++xBegin;
            ++yBegin;
          }

          if ( xBegin == table.x().end() ) {

            break;
          }
          else {

            if ( *gRight < *xBegin ) {

              *iter += integrator( *std::prev( xBegin ), *gRight,
                                   *std::prev( yBegin ),
                                   interpolator( *gRight,
                                                 *std::prev( xBegin ), *xBegin,
                                                 *std::prev( yBegin ), *yBegin ) );
            }
            else {

              *iter += integrator( *std::prev( xBegin ), *xBegin,
                                   *std::prev( yBegin ), *yBegin );
            }
          }
        }

        ++iter;
        ++gLeft;
        ++gRight;
      }

      return result;
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    AnalyticalIntegrator() = default;

    /**
     *  @brief Constructor
     *
     *  @param boundaries   the integration boundaries
     */
    AnalyticalIntegrator( std::vector< X > boundaries ) :
      boundaries_( std::move( boundaries ) ) {

      verifyBoundaries( this->boundaries() );
    }

    /**
     *  @brief Constructor
     *
     *  @param a   the lower limit of the integration interval
     *  @param b   the upper limit of the integration interval
     */
    AnalyticalIntegrator( X a, X b ) :
      AnalyticalIntegrator( std::vector< X >{ std::move( a ), std::move( b ) } ) {}

    /* methods */

    /**
     *  @brief Return the integration boundaries
     */
    const std::vector< X >& boundaries() const noexcept {

      return this->boundaries_;
    }

    /**
     *  @brief Return the number of integration intervals
     */
    unsigned int numberIntervals() const noexcept {

      return this->boundaries().size() - 1;
    }

    template < typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > operator()( const InterpolationTable< X, Y >& table ) const {

      auto interpolator = interpolation::LinearLinear();
      auto integrator = integration::LinearLinear();

      return this->integrate( interpolator, integrator, table );
    }

    template < typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > zerothMoment( const InterpolationTable< X, Y >& table ) const {

      return this->operator()( table );
    }

    template < typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > mean( const InterpolationTable< X, Y >& table ) const {

      auto interpolator = interpolation::LinearLinear();
      auto integrator = integration::LinearLinearMean();

      return this->integrate( interpolator, integrator, table );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

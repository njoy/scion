#ifndef NJOY_SCION_INTEGRATION_ADAPTIVE_GAUSSLOBATTO
#define NJOY_SCION_INTEGRATION_ADAPTIVE_GAUSSLOBATTO

// system includes
#include <array>
#include <optional>

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief The Gauss-Lobatto 4-point quadrature rule
   */
  template< typename X, typename Y = X >
  class AdaptiveGaussLobatto {

    /* type aliases */
    using I = decltype( std::declval< X >() * std::declval< Y >() );

    /* the interval type */

    #include "scion/integration/AdaptiveGaussLobatto/src/Interval.hpp"

    /* fields */
    std::vector< Interval > intervals_;

    /**
     *  @brief Return the current intervals
     */
    const std::vector< Interval >& intervals() const {

      return this->intervals_;
    }

    /**
     *  @brief Return the x values
     */
    std::vector< Interval >& intervals() {

      return this->intervals_;
    }

  public:

    /* methods */

    /**
     *  @brief Calculate the integral of a function over the interval [a, b]
     *
     *  @param[in] functor     the function to integrate
     *  @param[in] a           the lower bound of the integration interval
     *  @param[in] b           the upper bound of the integration interval
     *  @param[in] tolerance   the tolerance (default is 1e-8)
     */
    template < typename Functor >
    I operator()( Functor&& functor, const X& a, const X& b,
                  double tolerance = 1e-8 ) {

      this->intervals().clear();
      this->intervals().emplace_back( functor, a, b, functor( a ), functor( b ), true );

      // check for convergence
      I absolute = this->intervals().back().absoluteTolerance( tolerance );
      if ( this->intervals().back().cannotSubdivide() ||
           this->intervals().back().difference() - absolute <= 0. ) {

        return this->intervals().back().kronrod13Integral().value();
      }

      I total( 0. );
      while ( ! this->intervals().empty() ) {

        auto intervals = this->intervals().back().subdivide( functor );
        this->intervals().pop_back();
        for ( std::size_t i = 0; i < intervals.size(); ++i ) {

          if ( intervals[i].cannotSubdivide() ||
               intervals[i].difference() - absolute <= 0. ) {

            total += intervals[i].gaussLobattoIntegral();
          }
          else {

            this->intervals().emplace_back( std::move( intervals[i] ) );
          }
        }
      }

      return total;
    }
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

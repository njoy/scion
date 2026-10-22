#ifndef NJOY_SCION_INTEGRATION_COULOMBPENETRABILITY
#define NJOY_SCION_INTEGRATION_COULOMBPENETRABILITY

// system includes

// other includes
#include "scion/interpolation/CoulombPenetrability.hpp"
#include "scion/integration/AdaptiveGaussLobatto.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Coulomb Penetrability integration (LAW = 6)
   *
   *  The integral of a panel is calculated numerically using
   *  adaptive Gauss-Lobatto quadrature (with a tolerance of 1e-8).
   */
  class CoulombPenetrability {

  public:

    /**
     *  @brief Perform Coulomb Penetrability integration (LAW = 6)
     *
     *  @param[in] xLeft      the left value on the x interval
     *  @param[in] xRight     the right value on the x interval
     *  @param[in] yLeft      the left value on the y interval
     *  @param[in] yRight     the right value on the y interval
     *  @param[in] threshold  the reaction threshold value
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight,
                  const X& threshold ) const {

      if ( xLeft == xRight ) {

        return I( 0. );
      }
      else {

        auto functor = [&] ( const X& x ) {

          return interpolation::coulomb( x, xLeft, xRight, yLeft, yRight, threshold );
        };

        integration::AdaptiveGaussLobatto< X, Y > integrator;
        return integrator( functor, xLeft, xRight );
      }
    }
  };

  // integration function
  static constexpr CoulombPenetrability coulomb;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

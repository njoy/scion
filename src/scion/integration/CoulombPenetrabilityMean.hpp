#ifndef NJOY_SCION_INTEGRATION_COULOMBPENETRABILITYMEAN
#define NJOY_SCION_INTEGRATION_COULOMBPENETRABILITYMEAN

// system includes

// other includes
#include "scion/integration/CoulombPenetrability.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Coulomb penetrability mean integration
   *
   *  The integral of a panel is calculated numerically using adaptive
   *  Gauss-Lobatto quadrature (with a default tolerance of 1e-8).
   *
   *  @todo the integral has a closed form using the exponential integrals E1 and E3
   *        of a real argument
   */
  class CoulombPenetrabilityMean {

  public:

    /**
     *  @brief Perform Coulomb Penetrability integration of x * f(x)
     *
     *  @param[in] xLeft      the left value on the x interval
     *  @param[in] xRight     the right value on the x interval
     *  @param[in] yLeft      the left value on the y interval
     *  @param[in] yRight     the right value on the y interval
     *  @param[in] threshold  the reaction threshold value
     *  @param[in] tolerance  the tolerance for the adaptive quadrature (default 1e-8)
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ),
               typename T = decltype( std::declval< X >() / std::declval< X >() ) >
    I operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight,
                  const X& threshold, const T& tolerance = T( 1e-8 ) ) const {

      if ( xLeft == xRight ) {

        return I( 0. );
      }
      else {

        auto functor = [&] ( const X& x ) {

          return x * interpolation::coulomb( x, xLeft, xRight, yLeft, yRight, threshold );
        };

        integration::AdaptiveGaussLobatto< X, Y > integrator;
        return integrator( functor, xLeft, xRight, tolerance );
      }
    }
  };

  // integration function
  static constexpr CoulombPenetrabilityMean coulombMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

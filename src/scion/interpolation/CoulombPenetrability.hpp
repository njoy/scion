#ifndef NJOY_SCION_INTERPOLATION_COULOMBPENETRABILITY
#define NJOY_SCION_INTERPOLATION_COULOMBPENETRABILITY

// system includes
#include <cmath>

// other includes

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Coulomb Penetrability interpolation
   */
  class CoulombPenetrability {

  public:

    /* methods */

    /**
     *  @brief Perform Coulomb penetrability interpolation
     *
     *  @param[in] x           the value of x
     *  @param[in] xLeft       the left value on the x interval
     *  @param[in] xRight      the right value on the x interval
     *  @param[in] yLeft       the left value on the y interval
     *  @param[in] yRight      the right value on the y interval
     *  @param[in] threshold   the threshold value (threshold < xLeft)
     */
    template < typename X, typename Y >
    Y operator()( const X& x,
                  const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight,
                  const X& threshold ) const noexcept {

      const X aLeft  = 1.0 / std::sqrt( xLeft - threshold );
      const X aRight = 1.0 / std::sqrt( xRight - threshold );
      const X a      = 1.0 / std::sqrt( x - threshold );

      const X alpha = ( a - aLeft ) / ( aRight - aLeft );

      return ( 1.0 / x ) * std::pow( yRight * xRight, alpha ) * std::pow( yLeft * xLeft, 1.0 - alpha );
    }
  };

  // interpolation function
  static constexpr CoulombPenetrability coulomb;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTERPOLATION_COULOMBPENETRABILITY
#define NJOY_SCION_INTERPOLATION_COULOMBPENETRABILITY

// system includes
#include <math.h>

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Coulomb Penetrability interpolation 
   */
  template < typename X, typename Y >
  class CoulombPenetrability : public InterpolatorBase< CoulombPenetrability < X, Y > > {

    /* friend declarations */
    friend class InterpolatorBase< CoulombPenetrability< X, Y > >;

  public:

    /* type aliases */

  private:

    /* fields */
    X threshold_;

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param threshold  the threshold value
     */
    CoulombPenetrability( X threshold ) :
      threshold_( std::move( threshold ) ) {}

    /* interface implementation functions */

    /**
     *  @brief Perform Coulomb Penetrability interpolation 
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */

    Y interpolate( const X& x,
                   const X& xLeft, const X& xRight,
                   const Y& yLeft, const Y& yRight ) const noexcept {

      const X a1 = 1.0 / std::sqrt( xLeft - this->threshold_ );
      const X a2 = 1.0 / std::sqrt( xRight - this->threshold_ );
      const X a  = 1.0 / std::sqrt( x - this->threshold_ );

      const X alpha = ( a - a1 ) / ( a2 - a1 );

      return ( 1.0 / x ) * std::pow( yRight * xRight, alpha ) * std::pow( yLeft * xLeft, 1.0 - alpha );
    }

    /**
     *  @brief Return the threshold value
     */
    const X& threshold() const noexcept {

      return this->threshold_;
    }

  };

  // interpolation function
  // static constexpr CoulombPenetrability coulomb;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

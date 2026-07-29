#ifndef NJOY_SCION_INTEGRATION_COULOMBPENETRABILITY
#define NJOY_SCION_INTEGRATION_COULOMBPENETRABILITY

// system includes
#include <iostream>

// other includes
#include "scion/math/compare.hpp"
#include "scion/integration/IntegratorBase.hpp"
#include "scion/interpolation/CoulombPenetrability.hpp"
#include "scion/integration/AdaptiveGaussLobatto.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Coulomb Penetrability integration (LAW = 6)
   *
   *  The integral of a panel is calculated numerically
   */
  class CoulombPenetrability : public IntegratorBase< CoulombPenetrability > {

    /* friend declarations */
    friend class IntegratorBase< CoulombPenetrability >;


    /* interface implementation functions */

  public:
  
    /**
     *  @brief Perform Coulomb Penetrability integration (LAW = 6)
     *
     *
     *  @param[in] xLeft      the left value on the x interval
     *  @param[in] xRight     the right value on the x interval
     *  @param[in] yLeft      the left value on the y interval
     *  @param[in] yRight     the right value on the y interval
     *  @param[in] threshold  the reaction threshold value
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight,
                 const X& threshold ) const noexcept {

      // need to check this explicitly because the equation will return
      // NaN instead of zero
      if ( math::isClose( xLeft, xRight ) ) {

        return 0.0;
      }

      // create the interpolator 
      interpolation::CoulombPenetrability< X, Y > interpolator{ threshold };

      auto functor = [&] ( X x ) { return interpolator( x, xLeft, xRight, yLeft, yRight ); };
      
      integration::AdaptiveGaussLobatto< I > integrator{};

      return integrator( functor, xLeft, xRight );
    }


    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight, 
                  const X& threshold ) const {

     return this->integrate( xLeft, xRight, yLeft, yRight, threshold );
    }

  };

  // static function
  static constexpr CoulombPenetrability coulomb;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

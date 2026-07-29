#ifndef NJOY_SCION_INTEGRATION_COULOMBPENETRABILITYMEAN
#define NJOY_SCION_INTEGRATION_COULOMBPENETRABILITYMEAN

// system includes
#include <iostream>

// other includes
#include "scion/integration/CoulombPenetrability.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Coulomb Penetrability integration (LAW = 6)
   *
   *  The integral of a panel is calculated numerically
   */
  class CoulombPenetrabilityMean : public IntegratorBase< CoulombPenetrabilityMean > {

    /* friend declarations */
    friend class IntegratorBase< CoulombPenetrabilityMean >;


    /* interface implementation functions */

  public:
  
    /**
     *  @brief Perform Coulomb Penetrability integration of x * f(x)
     *
     *
     *  @param[in] xLeft      the left value on the x interval
     *  @param[in] xRight     the right value on the x interval
     *  @param[in] yLeft      the left value on the y interval
     *  @param[in] yRight     the right value on the y interval
     *  @param[in] threshold  the reaction threshold value
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
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

      auto functor = [&] ( X x ) { return x * interpolator( x, xLeft, xRight, yLeft, yRight ); };
      
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
  static constexpr CoulombPenetrabilityMean coulombMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

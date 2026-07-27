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
  template < typename X, typename Y >
  class CoulombPenetrability : public IntegratorBase< CoulombPenetrability< X, Y > > {

    /* friend declarations */
    friend class IntegratorBase< CoulombPenetrability< X, Y > >;

  private:

    /* fields */
    X threshold_;

    /* type aliases */
    using I = decltype( std::declval< X >() * std::declval< Y >() );

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
     *  @brief Perform Coulomb Penetrability integration (LAW = 6)
     *
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      // need to check this explicitly because the equation will return
      // NaN instead of zero
      if ( math::isClose( xLeft, xRight ) ) {

        return 0.0;
      }

      interpolation::CoulombPenetrability< X, Y > interpolator{ this->threshold_ };

      auto functor = [&] ( X x ) { return interpolator( x, xLeft, xRight, yLeft, yRight ); };
      
      integration::AdaptiveGaussLobatto< I > integrator{};

      return integrator( functor, xLeft, xRight );

    }
   
    /**
     *  @brief Return the threshold value
     */
    const X& threshold() const noexcept {

      return this->threshold_;
    }


  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

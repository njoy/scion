#ifndef NJOY_SCION_INTEGRATION_FIRSTMOMENTLINEARLINEAR
#define NJOY_SCION_INTEGRATION_FIRSTMOMENTLINEARLINEAR

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief First raw moment of a Linear-linear panel (y is linear in x)
   *
   *  The first raw moment or mean is defined as the integral of x * f(x)
   */
  class FirstMomentLinearLinear : public IntegratorBase< FirstMomentLinearLinear > {

    /* friend declarations */
    friend class IntegratorBase< FirstMomentLinearLinear >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-linear panel (y is linear in x)
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      auto delta = ( xRight - xLeft );
      auto slope = ( yRight - yLeft ) / delta / 3.;
      auto constant = 0.5 * ( xRight * yLeft - xLeft * yRight ) / delta;
      return xRight * xRight * ( slope * xRight + constant )
             - xLeft * xLeft * ( slope * xLeft + constant );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr FirstMomentLinearLinear firstMomentLinLin;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_FIRSTMOMENTLOGARITHMICLOGARITHMIC
#define NJOY_SCION_INTEGRATION_FIRSTMOMENTLOGARITHMICLOGARITHMIC

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief First raw moment of a logarithmic-logarithmic panel (ln(y) is linear in ln(x))
   *
   *  The first raw moment or mean is defined as the integral of x * f(x)
   *
   *  Since ln(y) is linear in ln(x), the function to be integrated is:
   *    y = y1 x exp(a ln(x/x1)) with a = ln(y2/y1) / ln(x2/x1)
   *      = ( y1 / x1**a ) x**(a+1)
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = int[x1,x2] ( y1 / x1**a ) x**(a+1) dx
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = ( y1 / x1**a ) ( x2**(a+2) - x1**(a+2) ) / (a+2)
   *                    = ( y1 x1**2 ) ( (x2/x1)**(a+2) - 1 ) / (a+2)
   */
  class FirstMomentLogarithmicLogarithmic : public IntegratorBase< FirstMomentLogarithmicLogarithmic > {

    /* friend declarations */
    friend class IntegratorBase< FirstMomentLogarithmicLogarithmic >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-logarithmic panel (y is linear in ln(x))
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

      auto slope = std::log( yRight / yLeft ) / std::log( xRight / xLeft );
      return yLeft * xLeft * xLeft * ( std::pow( xRight / xLeft, slope + 2. ) - 1. ) / ( slope + 2. );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr FirstMomentLogarithmicLogarithmic firstMomentLogLog;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

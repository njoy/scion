#ifndef NJOY_SCION_INTEGRATION_LINEARLOGARITHMICMEAN
#define NJOY_SCION_INTEGRATION_LINEARLOGARITHMICMEAN

// system includes
#include <array>
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"
#include "scion/math/horner.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Mean of a linear-logarithmic panel (y is linear in ln(x))
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   *
   *  The integral of a panel is calculated analytically using the following
   *  primitive function:
   *    int x ln(x) = x**2 / 2 ( ln(x) - 1 / 2 )
   *
   *  Since y is linear in ln(x), the panel is interpolated as:
   *    y = a x ( ln(x) - ln(x1) ) + x y1 with a = (y2 - y1) / ln(x2/x1)
   *
   *  The integral over the panel is then given by:
   *    int y dx = int ( y1 - a ln(x1) ) x + a x ln(x)
   *  which reduces to the following primitive function:
   *    int y dx = ( y1 - a ln(x1) ) x**2 / 2
   *               + a x**2 / 2 ( ln(x) - 1 / 2 )
   *             = a x**2 ln(x/x1) / 2 - a x**2 / 4 + y1 x**2 / 2
   *
   *  After applying this primitive and simplifying the result, we obtain:
   *    int[x1,x2] y dx = ( y2 x2**2 - y1 x1**2 ) / 2
   *                      - ( y2 - y1 ) ( x2**2 - x1**2 ) / ln(x2/x1)
   *
   *  When x2 - x1 becomes small, ( x2**2 - x1**2 ) / ln(x2/x1) reduces to
   *  x1**2 delta ( delta + 2 ) / ln(1+delta) with x2/x1 - 1 = delta. For small
   *  values of delta (chosen to be less than 1e-4), a truncated 5th order Taylor
   *  seriesexpansion is used to calculate delta ( delta + 2 ) / ln(1+delta).
   */
  class LinearLogarithmicMean : public IntegratorBase< LinearLogarithmicMean > {

    /* friend declarations */
    friend class IntegratorBase< LinearLogarithmicMean >;

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
                 const Y& yLeft, const Y& yRight ) const {

      const double delta = xRight / xLeft - 1.;
      if ( std::abs( delta ) < 1e-4 ) {

        static constexpr std::array< double, 6 > coefficients = {

          2.0, 2.0, 1.0 / 3.0, 0.0, -1.0 / 90.0, 1.0 / 90.0
        };
        return 0.5 * ( yRight * xRight * xRight - yLeft * xLeft * xLeft )
               - 0.25 * ( yRight - yLeft ) * xLeft * xLeft * math::horner( coefficients, delta );
      }
      else {

        return 0.5 * ( yRight * xRight * xRight - yLeft * xLeft * xLeft )
               - 0.25 * ( yRight - yLeft ) * ( xRight * xRight - xLeft * xLeft ) / std::log( xRight / xLeft );
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LinearLogarithmicMean linLogMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

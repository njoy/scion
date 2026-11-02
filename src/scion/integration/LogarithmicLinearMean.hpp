#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLINEARMEAN
#define NJOY_SCION_INTEGRATION_LOGARITHMICLINEARMEAN

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
   *  @brief Mean of a logarithmic-linear panel (ln(y) is linear in x)
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   *
   *  The mean of a panel is calculated analytically using the following
   *  primitive function:
   *    int x exp(x) = ( x - 1 ) exp(x)
   *
   *  Since y is linear in ln(x), the function to be integrated is:
   *    y = y1 x exp(a (x - x1)) with a = ln(y2/y1) / (x2 - x1)
   *      = y1 exp(-ax1) x exp(ax) with a = ln(y2/y1) / (x2 - x1)
   *
   *  The integral over the panel is then given by:
   *    int y dx = int y1 exp(-ax1) x exp(ax)
   *             = y1 exp(-ax1) int x exp(ax)
   *  which reduces to the following primitive function:
   *    int y dx = y1 exp(-ax1) (ax - 1) exp(ax) / a**2
   *
   *  After applying this primitive and simplifying the result, we obtain:
   *    int[x1,x2] y dx = ( x2 y2 - x1 y1 ) / a - ( y2 - y1 ) / a**2
   *
   *  When y2 - y1 becomes small, we can rewrite the integral as
   *    (x2 - x1)
   *    ( y1 delta / ln(1+delta)
   *      + (x2 - x1) ( ( 1 + delta ) ln(1+delta) - delta ) / ln(1+delta)**2 ).
   *
   *  For small values of delta (chosen to be less than 1e-4), a truncated
   *  Taylor series expansion is used to calculate delta / ln(1+delta)
   *  and ( ( 1 + delta ) ln(1+delta) - delta ) / ln(1+delta)**2.
   */
  class LogarithmicLinearMean : public IntegratorBase< LogarithmicLinearMean > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLinearMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a logarithmic-linear panel (ln(y) is linear in x)
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

      const double delta = ( yRight - yLeft ) / yLeft;
      if ( std::abs( delta ) < 1e-3 ) {

        static constexpr std::array< double, 6 > coefficients1 = {

          1.0, 0.5, -1.0 / 12.0, 1.0 / 24.0, -19.0 / 720.0, 3.0 / 160.0
        };
        static constexpr std::array< double, 6 > coefficients2 = {

          0.5, 1.0 / 3.0, -1.0 / 24.0, 7.0 / 360.0, -17.0 / 1440.0, 41.0 / 5040.0
        };
        return ( xRight - xLeft ) * yLeft
               * ( xLeft * math::horner( coefficients1, delta )
                   + ( xRight - xLeft ) * math::horner( coefficients2, delta ) );
      }
      else {

        double inverse = ( xRight - xLeft ) / std::log( yRight / yLeft );
        return inverse * ( ( xRight * yRight - xLeft * yLeft ) - inverse * ( yRight - yLeft ) );
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LogarithmicLinearMean logLinMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

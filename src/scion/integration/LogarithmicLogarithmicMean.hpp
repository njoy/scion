#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMICMEAN
#define NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMICMEAN

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
   *  @brief Mean of a logarithmic-logarithmic panel (ln(y) is linear in ln(x))
   *
   *  The moment of order n for a function f(x) is defined as the integral of x**n * f(x)
   *
   *  Since ln(y) is linear in ln(x), the function to be integrated is:
   *    y = y1 x**n exp(a ln(x/x1)) with a = ln(y2/y1) / ln(x2/x1)
   *      = ( y1 / x1**a ) x**(a+n)
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = int[x1,x2] ( y1 / x1**a ) x**(a+n) dx
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = ( y1 / x1**a ) ( x2**(a+n+1) - x1**(a+n+1) ) / (a+n+1)
   *                    = ( y1 x1**(n+1) ) ( (x2/x1)**(a+n+1) - 1 ) / (a+n+1)
   *
   *  The mean or first raw moment is defined as the integral of x * f(x) and is thus
   *  calculated as:
   *    int[x1,x2] y dx = ( y1 x1**2 ) ( (x2/x1)**(a+2) - 1 ) / (a+2)
   *
   *  This can be rearranged as:
   *    int[x1,x2] y dx = ( x2**2 y2 - x1**2 y1 ) / (a+2)
   *
   *  With u = (x2**2 y2)/(x1**2 y1) - 1 = deltay + deltax ( 2 + deltax ) ( 1 + deltay )
   *  (where deltax = ( x2 - x1 ) / x1 and deltay = ( y2 - y1 ) / y1), this becomes:
   *    int[x1,x2] y dx = y1 x1**2 u / ( ln(y2/y1) / ln(x2/x1) + 2 )
   *                    = y1 x1**2 ln(x2/x1) u / ln( u + 1 )
   *
   *  To avoid the singularity for a = -2 (where u = 0), a truncated Taylor series
   *  is used to calculate u / ln( u + 1 ) in the second form when |u| is small
   *  (using a 5e-3 tolerance).
   *
   *  When x2 - x1 and/or y2 - y1 are small, truncated Taylor series are used to
   *  calculate ln(x2/x1) and/or ln(y2/y1) (using a 5e-3 tolerance).
   */
  class LogarithmicLogarithmicMean : public IntegratorBase< LogarithmicLogarithmicMean > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLogarithmicMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a logarithmic-logarithmic panel (ln(y) is linear in ln(x))
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

      static constexpr std::array< double, 6 > coefficients1 = {

        1.0, -1.0 / 2.0, 1.0 / 3.0, -1.0 / 4.0, 1.0 / 5.0, -1.0 / 6.0
      };
      static constexpr std::array< double, 6 > coefficients2 = {

        1.0 / 2.0, -1.0 / 12.0, 1.0 / 24.0, -19.0 / 720.0, 3.0 / 160.0, -863.0 / 60480.0
      };

      double logx;
      const double deltax = ( xRight - xLeft ) / xLeft;
      if ( std::abs( deltax ) < 5e-3 ) {

        logx = deltax * math::horner( coefficients1, deltax );
      }
      else {

        logx = std::log1p( deltax );
      }

      double logy;
      const double deltay = ( yRight - yLeft ) / yLeft;
      if ( std::abs( deltay ) < 5e-3 ) {

        logy = deltay * math::horner( coefficients1, deltay );
      }
      else {

        logy= std::log1p( deltay );
      }

      const double numerator = deltay + deltax * ( 2. + deltax ) * ( 1. + deltay );
      if ( std::abs( numerator ) < 5e-3 ) {

        return yLeft * xLeft * xLeft * logx * ( 1. + numerator * math::horner( coefficients2, numerator ) );
      }
      else {

        return yLeft * xLeft * xLeft * numerator / ( logy / logx + 2.0);
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LogarithmicLogarithmicMean logLogMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

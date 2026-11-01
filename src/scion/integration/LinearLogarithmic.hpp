#ifndef NJOY_SCION_INTEGRATION_LINEARLOGARITHMIC
#define NJOY_SCION_INTEGRATION_LINEARLOGARITHMIC

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
   *  @brief Linear-logarithmic integration (y is linear in ln(x))
   *
   *  The integral of a panel is calculated analytically using the following
   *  primitive function:
   *    int ln(x) =  x ln(x) - x
   *
   *  Since y is linear in ln(x), the panel is interpolated as:
   *    y = a ( ln(x) - ln(x1) ) + y1 with a = (y2 - y1) / ln(x2/x1)
   *
   *  The integral over the panel is then given by:
   *    int y dx = int y1 - a ln(x1) + a ln(x)
   *  which reduces to the following primitive function:
   *    int y dx = ( y1 - a ln(x1) ) x + a ( x ln(x) - x )
   *             = a x ln(x/x1) + ( y1 - a ) x
   *
   *  After applying this primitive and simplifying the result, we obtain:
   *    int[x1,x2] y dx = x2 y2 - x1 y1 - ( y2 - y1 ) ( x2 - x1 ) / ln(x2/x1)
   *
   *  When x2 - x1 becomes small, ( x2 - x1 ) / ln(x2/x1) reduces to
   *  x1 delta / ln(1+delta) with x2/x1 - 1 = delta. For small values of
   *  delta (chosen to be less than 1e-4), a truncated 5th order Taylor series
   *  expansion is used to calculate delta / ln(1+delta).
   */
  class LinearLogarithmic : public IntegratorBase< LinearLogarithmic > {

    /* friend declarations */
    friend class IntegratorBase< LinearLogarithmic >;

    /* interface implementation functions */

    /**
     *  @brief Perform linear-logarithmic integration (y is linear in ln(x))
     *
     *  There is the potential of a singularity when the two x values are the same. In
     *  practical applications this will never happen since the operator() takes care of
     *  checking for this exact possibility (when the x values are the same, the integral is 0).
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const {

      const double delta = xRight / xLeft - 1.;
      if ( std::abs( delta ) < 1e-4 ) {

        static constexpr std::array< double, 6 > coefficients = {

          1.0, 0.5, -1.0 / 12.0, 1.0 / 24.0, -19.0 / 720.0, 3.0 / 160.0
        };
        return xRight * yRight - xLeft * yLeft
               - (yRight - yLeft) * xLeft * math::horner( coefficients, delta );
      }
      else {

        return xRight * yRight - xLeft * yLeft
               - ( yRight - yLeft ) * ( xRight - xLeft ) / std::log( xRight / xLeft );
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LinearLogarithmic linlog;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

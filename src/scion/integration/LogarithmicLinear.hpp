#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLINEAR
#define NJOY_SCION_INTEGRATION_LOGARITHMICLINEAR

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
   *  @brief Logarithmic-linear integration (ln(y) is linear in x)
   *
   *  The integral of a panel is calculated analytically using the following
   *  primitive function:
   *    int exp(ax) =  exp(ax) / a
   *
   *  Since ln(y) is linear in x, the panel is interpolated as:
   *    y = exp(a (x - x1) + ln(y1)) with a = ln(y2/y1) / (x2 - x1)
   *      = y1 exp(a (x - x1))
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = y1 int[x1,x2] exp(a (x - x1))
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = y1 / a (exp(a (x2 - x1)) - exp(a (x1 - x1)))
   *                    = y1 / a (exp(a (x2 - x1)) - 1)
   *                    = y1 / a (y2 / y1 - 1)
   *                    = (x2 - x1) (y2 - y1) / ln(y2/y1)
   *
   *  When y2 - y1 becomes small, ( y2 - y1 ) / ln(y2/y1) reduces to
   *  y1 delta / ln(1+delta) with ( y2 - y1 ) / y1 = delta. For small values of
   *  delta (chosen to be less than 1e-4), a truncated Taylor series
   *  expansion is used to calculate delta / ln(1+delta).
   */
  class LogarithmicLinear : public IntegratorBase< LogarithmicLinear > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLinear >;

    /* interface implementation functions */

    /**
     *  @brief Perform logarithmic-linear integration (ln(y) is linear in x)
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

      const double delta = ( yRight - yLeft ) / yLeft;
      if ( std::abs( delta ) < 1e-4 ) {

        static constexpr std::array< double, 6 > coefficients = {

          1.0, 0.5, -1.0 / 12.0, 1.0 / 24.0, -19.0 / 720.0, 3.0 / 160.0
        };
        return ( xRight - xLeft ) * yLeft * math::horner( coefficients, delta );
      }
      else {

        return ( xRight - xLeft ) * ( yRight - yLeft ) / std::log1p( delta );
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LogarithmicLinear loglin;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

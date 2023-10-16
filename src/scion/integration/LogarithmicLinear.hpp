#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLINEAR
#define NJOY_SCION_INTEGRATION_LOGARITHMICLINEAR

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

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
                 const Y& yLeft, const Y& yRight ) const noexcept {

      if ( xLeft == xRight ) {

        return I( 0. );
      }
      else {

        return yLeft * ( xRight - xLeft ) / std::log( yRight / yLeft )
               * ( yRight / yLeft - 1. );
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

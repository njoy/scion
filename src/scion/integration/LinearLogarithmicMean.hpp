#ifndef NJOY_SCION_INTEGRATION_LINEARLOGARITHMICMEAN
#define NJOY_SCION_INTEGRATION_LINEARLOGARITHMICMEAN

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Mean of a linear-logarithmic panel (y is linear in ln(x))
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   *
   *  The mean of a panel is calculated analytically using the following
   *  primitive function:
   *    int x ln(x) = x**2 / 2 ( ln(x) - 1 / 2 )
   *
   *  Since y is linear in ln(x), the function to be integrated is:
   *    y = a x ln(x/x1) + y1 x with a = (y2 - y1) / ln(x2/x1)
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = int[x1,x2] a x ln(x/x1) dx + y1 (x2**2 - x1**2) / 2
   *
   *  By substituting z = x/x1 in the first term, we obtain:
   *    int[x1,x2] y dx = int[1,x2/x1] a x1**2 z ln(z) dz + y1 (x2**2 - x1**2) / 2
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = a / 2 (x2**2 (ln(x2/x1) - 1 / 2) + x1**2 / 2) + y1 (x2**2 - x1**2) / 2
   */
  class LinearLogarithmicMean : public IntegratorBase< LinearLogarithmicMean > {

    /* friend declarations */
    friend class IntegratorBase< LinearLogarithmicMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-logarithmic panel (y is linear in ln(x))
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
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      return 0.5 * ( ( yRight - yLeft ) / std::log( xRight / xLeft )
             * ( xRight * xRight * ( std::log( xRight / xLeft ) - 0.5 ) + 0.5 * xLeft * xLeft )
             + yLeft * ( xRight * xRight - xLeft * xLeft ) );
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

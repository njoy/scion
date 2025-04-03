#ifndef NJOY_SCION_INTEGRATION_LINEARLOGARITHMIC
#define NJOY_SCION_INTEGRATION_LINEARLOGARITHMIC

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

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
   *    y = a ln(x/x1) + y1 with a = (y2 - y1) / ln(x2/x1)
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = int[x1,x2] a ln(x/x1) dx + y1 (x2 - x1)
   *
   *  By substituting z = x/x1 in the first term, we obtain:
   *    int[x1,x2] y dx = int[1,x2/x1] a x1 ln(z) dz + y1 (x2 - x1)
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = a x1 (x2/x1 (ln(x2/x1) - 1) + 1) + y1 (x2 - x1)
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
                 const Y& yLeft, const Y& yRight ) const noexcept {

      return ( yRight - yLeft ) / std::log( xRight / xLeft )
             * xLeft * ( xRight / xLeft * ( std::log( xRight / xLeft ) - 1. ) + 1. )
             + yLeft * ( xRight - xLeft );
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

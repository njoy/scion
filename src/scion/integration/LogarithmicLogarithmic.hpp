#ifndef NJOY_SCION_INTERPOLATION_LOGARITHMICLOGARITHMIC
#define NJOY_SCION_INTERPOLATION_LOGARITHMICLOGARITHMIC

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Logarithmic-logarithmic integration (ln(y) is linear in ln(x))
   *
   *  Since ln(y) is linear in ln(x), the panel is interpolated as:
   *    y = exp(a ln(x/x1) + ln(y1)) with a = ln(y2/y1) / ln(x2/x1)
   *      = y1 (x/x1)^a
   *
   *  The integral over the panel is then given by:
   *    int[x1,x2] y dx = y1 int[x1,x2] (x/x1)^a
   *  which simplifies to:
   *    int[x1,x2] y dx = x1 y1 / (a + 1) ((x2/x1)^(a+1) - 1)
   */
  class LogarithmicLogarithmic : public IntegratorBase< LogarithmicLogarithmic > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLogarithmic >;

    /* interface implementation functions */

    /**
     *  @brief Perform logarithmic-logarithmic integration (ln(y) is linear in ln(x))
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y >
    Y integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      return xLeft * yLeft / ( std::log( yRight / yLeft ) / std::log( xRight / xLeft ) + 1. )
             * ( std::pow( xRight / xLeft,
                           std::log( yRight / yLeft ) / std::log( xRight / xLeft ) + 1. )
                 - 1. );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LogarithmicLogarithmic loglog;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

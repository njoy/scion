#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMICMEAN
#define NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMICMEAN

// system includes
#include <cmath>

// other includes
#include "tools/Log.hpp"
#include "scion/math/compare.hpp"
#include "scion/integration/IntegratorBase.hpp"

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
   */
  class LogarithmicLogarithmicMean : public IntegratorBase< LogarithmicLogarithmicMean > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLogarithmicMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-logarithmic panel (y is linear in ln(x))
     *
     *  There is the potential of a singularity when ln(y2/y1) / ln(x2/x1) equals -2.
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

      auto slope = std::log( yRight / yLeft ) / std::log( xRight / xLeft );
      if ( math::isClose( slope, -2. ) ) {

        Log::error( "Possible singularity since slope close to -2, contact a developer" );
        throw std::exception();
      }

      return yLeft * xLeft * xLeft * ( std::pow( xRight / xLeft, slope + 2. ) - 1. ) / ( slope + 2. );
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

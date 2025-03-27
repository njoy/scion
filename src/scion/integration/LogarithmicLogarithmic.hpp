#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMIC
#define NJOY_SCION_INTEGRATION_LOGARITHMICLOGARITHMIC

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
   *  @brief Logarithmic-logarithmic integration (ln(y) is linear in ln(x))
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
   *  The integral of f(x) is thus calculated as:
   *    int[x1,x2] y dx = ( y1 x1 ) ( (x2/x1)**(a+1) - 1 ) / (a+1)
   */
  class LogarithmicLogarithmic : public IntegratorBase< LogarithmicLogarithmic > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLogarithmic >;

    /* interface implementation functions */

    /**
     *  @brief Perform logarithmic-logarithmic integration (ln(y) is linear in ln(x))
     *
     *  There is the potential of a singularity when ln(y2/y1) / ln(x2/x1) equals -1.
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

      const auto slope = std::log( yRight / yLeft ) / std::log( xRight / xLeft );
      if ( math::isClose( slope, -1. ) ) {

        Log::error( "Possible singularity since slope close to -1, contact a developer" );
        throw std::exception();
      }

      return yLeft * xLeft / ( slope + 1. )
             * ( std::pow( xRight / xLeft, slope + 1. ) - 1. );
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

#ifndef NJOY_SCION_INTEGRATION_LOGARITHMICLINEARMEAN
#define NJOY_SCION_INTEGRATION_LOGARITHMICLINEARMEAN

// system includes
#include <cmath>

// other includes
#include "scion/integration/IntegratorBase.hpp"

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
   *    int[x1,x2] y dx = int[x1,x2] y1 exp(-ax1) x exp(ax) dx
   *
   *  By substituting z = ax in the integral, we obtain:
   *    int[x1,x2] y dx = int[ax1,ax2] ( y1 / a**2 ) exp(-ax1) z exp(z) dz
   *  which simplifies to (using the primitive):
   *    int[x1,x2] y dx = ( y1 / a**2 ) exp(-ax1) ( ( ax2 - 1 ) exp( ax2 ) - ( ax1 - 1 ) exp( ax1 ) )
   *                    = ( y1 / a**2 ) ( ( ax2 - 1 ) exp( a ( x2 - x1 ) ) - ( ax1 - 1 ) )
   */
  class LogarithmicLinearMean : public IntegratorBase< LogarithmicLinearMean > {

    /* friend declarations */
    friend class IntegratorBase< LogarithmicLinearMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-logarithmic panel (y is linear in ln(x))
     *
     *  There is the potential of a singularity when the two y values are the same.
     *
     *  There is also the potential of a singularity when the two x values are the same. In
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

      auto slope = std::log( yRight / yLeft ) / ( xRight - xLeft );
      return yLeft / slope / slope *
             ( ( slope * xRight - 1. ) * std::exp( slope * ( xRight - xLeft ) )
             - ( slope * xLeft - 1. ) );
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

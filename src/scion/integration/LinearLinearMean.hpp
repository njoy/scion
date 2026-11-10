#ifndef NJOY_SCION_INTEGRATION_LINEARLINEARMEAN
#define NJOY_SCION_INTEGRATION_LINEARLINEARMEAN

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Mean of a linear-linear panel (y is linear in x)
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   *
   *  Since y is linear in x, the function to be integrated is:
   *    y = x (y1 + a (x - x1)) with a = (y2 - y1) / (x2 - x1)
   *
   *  By substituting x = x1 + (x2 - x1) t = x1 + h t in this function:
   *    y = (x1 + h t) (y1 + (y2 - y1) t)
   *
   *  Since dx = h dt and since t = 0 for x = x1 and t = 1 for x = x2
   *  the integral becomes:
   *    int[x1,x2] x y dx
   *      = h int[0,1] (x1 + h t) (y1 + (y2 - y1) t) dt
   *      = h int[0,1] x1 y1 + (x1 (y2 - y1) + h y1) t + h (y2-y1) t**2 dt
   *
   *  Since int[0,1] t**n dt = 1 / (n + 1), we can show that after some
   *  simplification the integral reduces to the following form:
   *    int[x1,x2] x y dx = h ( x1 (y1 + y2) / 2 + h (y1 + 2 y2) / 6 )
   *
   *  This form does not have a singularity for x1 = x2, nor does it have numerical
   *  issues when x2 - x1 becomes small. It has less operations and should be
   *  more efficient than the previous implementations.
   */
  class LinearLinearMean : public IntegratorBase< LinearLinearMean > {

    /* friend declarations */
    friend class IntegratorBase< LinearLinearMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-linear panel (y is linear in x)
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

      const auto delta = xRight - xLeft;
      return delta * ( 0.5 * xLeft * ( yLeft + yRight ) + delta * ( yLeft + 2. * yRight ) / 6. );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LinearLinearMean linLinMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

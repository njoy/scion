#ifndef NJOY_SCION_INTERPOLATION_LINEARLINEAR
#define NJOY_SCION_INTERPOLATION_LINEARLINEAR

// system includes

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Linear-linear interpolation (y is linear in x)
   */
  class LinearLinear : public InterpolatorBase< LinearLinear > {

  public:

    /**
     *  @brief Perform linear-linear interpolation (y is linear in x)
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y >
    Y interpolate( const X& x,
                   const X& xLeft, const X& xRight,
                   const Y& yLeft, const Y& yRight ) const noexcept {

      return yLeft + ( yRight - yLeft ) / ( xRight - xLeft ) * ( x - xLeft );
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LinearLinear linlin;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

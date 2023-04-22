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
   *  @brief Linear-linear interpolation
   */
  class LinearLinear : public InterpolatorBase< LinearLinear > {

  public:

    /**
     *  @brief Perform linear-linear interpolation
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

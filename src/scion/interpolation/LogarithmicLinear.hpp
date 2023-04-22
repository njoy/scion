#ifndef NJOY_SCION_INTERPOLATION_LOGARITHMICLINEAR
#define NJOY_SCION_INTERPOLATION_LOGARITHMICLINEAR

// system includes

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Logarithmic-linear interpolation (ln(y) is linear in x)
   */
  class LogarithmicLinear : public InterpolatorBase< LogarithmicLinear > {

  public:

    /**
     *  @brief Perform logarithmic-linear interpolation
     */
    template < typename X, typename Y >
    Y interpolate( const X& x,
                   const X& xLeft, const X& xRight,
                   const Y& yLeft, const Y& yRight ) const noexcept {

      return yLeft * std::pow( yRight / yLeft,
                               ( x - xLeft ) / ( xRight - xLeft ) );
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LogarithmicLinear loglin;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

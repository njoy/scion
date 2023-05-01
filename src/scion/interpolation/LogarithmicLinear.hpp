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
     *  @brief Perform logarithmic-linear interpolation (ln(y) is linear in x)
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

      return yLeft * std::exp( std::log( yRight / yLeft )
                               * ( x - xLeft ) / ( xRight - xLeft ) );
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LogarithmicLinear loglin;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

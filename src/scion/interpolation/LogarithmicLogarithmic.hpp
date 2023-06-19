#ifndef NJOY_SCION_INTERPOLATION_LOGARITHMICLOGARITHMIC
#define NJOY_SCION_INTERPOLATION_LOGARITHMICLOGARITHMIC

// system includes

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))
   */
  class LogarithmicLogarithmic : public InterpolatorBase< LogarithmicLogarithmic > {

  public:

    /**
     *  @brief Perform logarithmic-logarithmic interpolation (ln(y) is linear in ln(x))
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

      return yLeft * std::pow( yRight / yLeft, std::log( x / xLeft ) / std::log( xRight / xLeft ) );
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LogarithmicLogarithmic loglog;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

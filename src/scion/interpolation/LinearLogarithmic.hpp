#ifndef NJOY_SCION_INTERPOLATION_LINEARLOGARITHMIC
#define NJOY_SCION_INTERPOLATION_LINEARLOGARITHMIC

// system includes

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Linear-logarithmic interpolation (y is linear in ln(x))
   */
  class LinearLogarithmic : public InterpolatorBase< LinearLogarithmic > {

  public:

    /**
     *  @brief Perform linear-logarithmic interpolation
     */
    template < typename X, typename Y >
    Y interpolate( const X& x,
                   const X& xLeft, const X& xRight,
                   const Y& yLeft, const Y& yRight ) const noexcept {

      return yLeft + ( yRight - yLeft )
                   / std::log( xRight / xLeft )
                   * std::log( x / xLeft );
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LinearLogarithmic linlog;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

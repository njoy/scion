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

    /* friend declarations */
    friend class InterpolatorBase< LinearLogarithmic >;

    /* interface implementation functions */

    /**
     *  @brief Perform linear-logarithmic interpolation (y is linear in ln(x))
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

      return yLeft + ( yRight - yLeft )
                   / std::log( xRight / xLeft )
                   * std::log( x / xLeft );
    }

  public:

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr LinearLogarithmic linlog;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTERPOLATION_HISTOGRAM
#define NJOY_SCION_INTERPOLATION_HISTOGRAM

// system includes

// other includes
#include "scion/interpolation/InterpolatorBase.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Histogram interpolation (y is constant in x)
   */
  class Histogram : public InterpolatorBase< Histogram > {

  public:

    /**
     *  @brief Perform histogram interpolation (y is constant in x)
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y >
    Y interpolate( const X& x,
                   const X&, const X&,
                   const Y& yLeft, const Y& ) const noexcept {

      return yLeft;
    }

    using InterpolatorBase::operator();
  };

  // interpolation function
  static constexpr Histogram histogram;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

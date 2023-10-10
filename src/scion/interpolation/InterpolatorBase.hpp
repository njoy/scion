#ifndef NJOY_SCION_INTERPOLATION_INTERPOLATORBASE
#define NJOY_SCION_INTERPOLATION_INTERPOLATORBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Base class for interpolator objects for tabulated data
   *
   *  This base class provides the common interface for all interpolator objects.
   */
  template < typename Derived >
  class InterpolatorBase {

  public:

    /* methods */

    /**
     *  @brief Perform interpolation
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y >
    Y operator()( const X& x,
                  const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) const noexcept {

      return static_cast< const Derived* >( this )->interpolate( x, xLeft, xRight, yLeft, yRight );
    }
  };

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

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
     *  @brief Perform interpolation on x,y tabulated data
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

    /**
     *  @brief Perform interpolation on x,f(y) tabulated data
     *
     *  This interpolation works by first evaluating the functions z = f(y) for the value
     *  of y, and then performing the normal interpolation on the interval defined by
     *  xl,zl and xr,zr as illustrated here:
     *
     *             fl(y)
     *    xl - - - # - - - - > left function of y
     *             |
     *    x  - - - *
     *             |
     *    xr - - - # - - - - > right function of y
     *             |
     *             fr(y)
     *
     *  As such, this does not do unit-base interpolation.
     *
     *  Since we can reuse the operator() on this base class so the derived class
     *  does not need to implement this particular interpolation operation.
     *
     *  @param[in] x        the value of x
     *  @param[in] y        the value of y
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] fLeft    the left function on the y axis
     *  @param[in] fRight   the right function on the y axis
     */
    template < typename X, typename Y, typename FLeft, typename FRight = FLeft,
               typename Z = decltype( std::declval< FLeft >()( std::declval< Y >() ) ) >
    Z operator()( const X& x, const Y& y,
                  const X& xLeft, const X& xRight,
                  const FLeft& fLeft, const FRight& fRight ) const noexcept {

      return this->operator()( x, xLeft, xRight, fLeft( y ), fRight( y ) );
    }
  };

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

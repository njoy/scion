#ifndef NJOY_SCION_INTEGRATION_INTEGRATORBASE
#define NJOY_SCION_INTEGRATION_INTEGRATORBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Base class for analytical integrator objects for tabulated data
   *
   *  This base class provides the common interface for all integrator objects.
   *  These are the integral equivalents of the interpolators.
   */
  template < typename Derived >
  class IntegratorBase {

  public:

    /* methods */

    /**
     *  @brief Perform integration
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) const noexcept {

      if ( xLeft == xRight ) {

        return I( 0. );
      }
      else {

        return static_cast< const Derived* >( this )->integrate( xLeft, xRight, yLeft, yRight );
      }
    }
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

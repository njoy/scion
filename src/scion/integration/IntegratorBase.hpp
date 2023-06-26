#ifndef NJOY_SCION_INTEGRATION_INTEGRATORBASE
#define NJOY_SCION_INTEGRATION_INTEGRATORBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Base class for analytical integrator objects
   *
   *  This base class provides the common interface for all integrator objects.
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
    template < typename X, typename Y >
    Y operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) const noexcept {

      return static_cast< const Derived* >( this )->integrate( xLeft, xRight, yLeft, yRight );
    }
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

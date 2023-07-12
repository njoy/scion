#ifndef NJOY_SCION_INTEGRATION_LINEARLINEAR
#define NJOY_SCION_INTEGRATION_LINEARLINEAR

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Linear-linear integration (y is linear in x)
   *
   *  The integral of a panel is calculated analytically using the trapezoid rule.
   */
  class LinearLinear : public IntegratorBase< LinearLinear > {

    /* friend declarations */
    friend class IntegratorBase< LinearLinear >;

    /* interface implementation functions */

    /**
     *  @brief Perform linear-linear integration (y is linear in x)
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      if ( xLeft == xRight ) {

        return I( 0. );
      }
      else {

        return 0.5 * ( xRight - xLeft ) * ( yLeft + yRight );
      }
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LinearLinear linlin;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

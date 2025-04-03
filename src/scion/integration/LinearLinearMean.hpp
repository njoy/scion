#ifndef NJOY_SCION_INTEGRATION_LINEARLINEARMEAN
#define NJOY_SCION_INTEGRATION_LINEARLINEARMEAN

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Mean of a linear-linear panel (y is linear in x)
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   */
  class LinearLinearMean : public IntegratorBase< LinearLinearMean > {

    /* friend declarations */
    friend class IntegratorBase< LinearLinearMean >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a linear-linear panel (y is linear in x)
     *
     *  There is the potential of a singularity when the two x values are the same since delta is
     *  zero. In practical applications this will never happen since the operator() takes care of
     *  checking for this exact possibility (when the x values are the same, the integral is 0).
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      auto delta = ( xRight - xLeft );
      auto slope = ( yRight - yLeft ) / delta / 3.;
      auto constant = 0.5 * ( xRight * yLeft - xLeft * yRight ) / delta;
      return xRight * xRight * ( slope * xRight + constant )
             - xLeft * xLeft * ( slope * xLeft + constant );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr LinearLinearMean linLinMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

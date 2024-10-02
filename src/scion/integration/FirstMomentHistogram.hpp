#ifndef NJOY_SCION_INTEGRATION_FIRSTMOMENTHISTOGRAM
#define NJOY_SCION_INTEGRATION_FIRSTMOMENTHISTOGRAM

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief First raw moment of a histogram panel (y is constant in x)
   *
   *  The first raw moment or mean is defined as the integral of x * f(x)
   */
  class FirstMomentHistogram : public IntegratorBase< FirstMomentHistogram > {

    /* friend declarations */
    friend class IntegratorBase< FirstMomentHistogram >;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a histogram panel (y is constant in x)
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& ) const noexcept {

      return 0.5 * yLeft * ( xRight - xLeft ) * ( xRight + xLeft );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr FirstMomentHistogram firstMomentHistogram;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

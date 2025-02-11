#ifndef NJOY_SCION_INTEGRATION_HISTOGRAMMEAN
#define NJOY_SCION_INTEGRATION_HISTOGRAMMEAN

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Mean of a histogram panel (y is constant in x)
   *
   *  The mean or first raw moment is defined as the integral of x * f(x)
   */
  class HistogramMean : public IntegratorBase< HistogramMean > {

    /* friend declarations */
    friend class IntegratorBase< HistogramMean >;

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
  static constexpr HistogramMean histogramMean;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

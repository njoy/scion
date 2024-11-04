#ifndef NJOY_SCION_INTEGRATION_HISTOGRAMVARIANCE
#define NJOY_SCION_INTEGRATION_HISTOGRAMVARIANCE

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Variance of a histogram panel (y is constant in x)
   *
   *  The variance or second central moment is defined as the integral 
   *  of (x-mu)**2 * f(x) with mu the mean value of x.
   */
  template < typename X >
  class HistogramVariance : public IntegratorBase< HistogramVariance< X > > {

    /* friend declarations */
    friend class IntegratorBase< HistogramVariance< X > >;

    /* fields */
    X mean_;

    /* interface implementation functions */

    /**
     *  @brief Perform first raw moment integration of a histogram panel (y is constant in x)
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() * 
                                      std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& ) const noexcept {

      return yLeft * ( ( xRight * xRight * xRight - xLeft * xLeft * xLeft ) / 3. 
                       - this->mean_ * ( xRight * xRight - xLeft * xLeft )
                       + this->mean_ * this->mean_ * ( xRight - xLeft ) );
    }

  public:

    /* interface implementation functions */

    /**
     *  @brief Constructor
     *
     *  @param[in] mean    the mean x value
     */
    HistogramVariance( X mean ) noexcept : mean_( std::move( mean ) ) {}

    using IntegratorBase< HistogramVariance< X > >::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

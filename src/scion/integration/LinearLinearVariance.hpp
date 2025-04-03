#ifndef NJOY_SCION_INTEGRATION_LINEARLINEARVARIANCE
#define NJOY_SCION_INTEGRATION_LINEARLINEARVARIANCE

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Variance of a linear-linear panel (y is linear in x)
   *
   *  The variance or second central moment is defined as the integral
   *  of (x-mu)**2 * f(x) with mu the mean value of x.
   */
  template < typename X >
  class LinearLinearVariance : public IntegratorBase< LinearLinearVariance< X > > {

    /* friend declarations */
    friend class IntegratorBase< LinearLinearVariance< X > >;

    /* fields */
    X mean_;

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
    template < typename Y,
               typename I = decltype( std::declval< X >() * std::declval< X >() *
                                      std::declval< X >() * std::declval< Y >() ) >
    I integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& yRight ) const noexcept {

      auto delta = ( xRight - xLeft );
      auto slope = ( yRight - yLeft ) / delta;
      auto constant = ( xRight * yLeft - xLeft * yRight ) / delta;

      auto a = slope / 4.;
      auto b = ( constant - 2. * slope * this->mean_ ) / 3.;
      auto c = ( slope * this->mean_ - 2. * constant ) * this->mean_ / 2.;
      auto d = constant * this->mean_ * this->mean_ ;
      return   ( ( ( a * xRight + b ) * xRight + c ) * xRight + d ) * xRight
             - ( ( ( a * xLeft + b ) * xLeft + c ) * xLeft + d ) * xLeft;
    }

  public:

    /**
     *  @brief Constructor
     *
     *  @param[in] mean    the mean x value
     */
    LinearLinearVariance( X mean ) noexcept : mean_( std::move( mean ) ) {}

    /* interface implementation functions */

    using IntegratorBase< LinearLinearVariance< X > >::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

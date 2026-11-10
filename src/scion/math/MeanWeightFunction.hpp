#ifndef NJOY_SCION_MATH_MEANWEIGHTFUNCTION
#define NJOY_SCION_MATH_MEANWEIGHTFUNCTION

// system includes

// other includes
#include "scion/math/WeightFunctionBase.hpp"
#include "scion/integration.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A weight function w(x) = x
   *
   *  Numerical integration using adaptive Gauss-Lobatto is used for panels
   *  with Coulomb penetrability interpolation. Because we use adaptive Gauss-Lobatto,
   *  the relative tolerance given (default of 1e-8) is the targeted relative tolerance.
   *  In practice the real error can be far smaller.
   */
  template < typename X, typename T = decltype( std::declval< X >() / std::declval< X >() ) >
  class MeanWeightFunction : public WeightFunctionBase< MeanWeightFunction< X, T >, X, X > {

    /* friend declarations */

    friend class WeightFunctionBase< MeanWeightFunction< X, T >, X, X >;

    /* type aliases */

    using Parent = WeightFunctionBase< MeanWeightFunction< X, T >, X, X >;

    /* fields */

    T tolerance_;

    /* interface implementation functions */

    /**
     *  @brief Evaluate the weight function
     */
    X evaluate( const X& x ) const noexcept {

      return x;
    }

    /**
     *  @brief Calculate the integral of weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< X >() ) >
    I calculateIntegral( const X& xLeft, const X& xRight ) const {

      return integration::linlin( xLeft, xRight, xLeft, xRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using histogram interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateHistogramIntegral( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const {

      return integration::histogramMean( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-lin interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateLinearLinearIntegral( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight ) const {

      return integration::linLinMean( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-log interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateLinearLogarithmicIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      return integration::linLogMean( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-lin interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateLogarithmicLinearIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      return integration::logLinMean( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-log interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the left y-value of the tabulated function
     *  @param yRight   the right y-value of the tabulated function
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateLogarithmicLogarithmicIntegral( const X& xLeft, const X& xRight,
                                               const Y& yLeft, const Y& yRight ) const {

      return integration::logLogMean( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * x * f(x) over a panel using Coulomb Penetrability interpolation
     *
     *  @param xLeft       the left boundary of the panel
     *  @param xRight      the right boundary of the panel
     *  @param yLeft       the left y-value of the tabulated function
     *  @param yRight      the right y-value of the tabulated function
     *  @param threshold   the reaction threshold
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< X >() ) >
    I calculateCoulombPenetrabilityIntegral( const X& xLeft, const X& xRight,
                                             const Y& yLeft, const Y& yRight,
                                             const X& threshold ) const {

      return integration::coulombMean( xLeft, xRight, yLeft, yRight, threshold,
                                       this->tolerance() );
    }

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param tolerance   the targeted numerical integration tolerance (default 1e-8)
     */
    MeanWeightFunction( T tolerance = T( 1e-8 ) ) :
      tolerance_( std::move( tolerance ) ) {}

    /* methods */

    /**
     *  @brief Return the targeted numerical integration tolerance
     */
    const T& tolerance() const noexcept {

      return this->tolerance_;
    }

    using Parent::operator();
    using Parent::integral;
    using Parent::integrateHistogram;
    using Parent::integrateLinearLinear;
    using Parent::integrateLinearLogarithmic;
    using Parent::integrateLogarithmicLinear;
    using Parent::integrateLogarithmicLogarithmic;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

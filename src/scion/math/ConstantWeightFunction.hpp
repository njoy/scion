#ifndef NJOY_SCION_MATH_CONSTANTWEIGHTFUNCTION
#define NJOY_SCION_MATH_CONSTANTWEIGHTFUNCTION

// system includes

// other includes
#include "scion/math/WeightFunctionBase.hpp"
#include "scion/integration.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A weight function w(x) = c
   *
   *  Numerical integration using adaptive Gauss-Lobatto is used for panels
   *  with Coulomb penetrability interpolation. Because we use adaptive Gauss-Lobatto,
   *  the relative tolerance given (default of 1e-8) is the targeted relative tolerance.
   *  In practice the real error can be far smaller.
   */
  template < typename X, typename W, typename T = decltype( std::declval< X >() / std::declval< X >() ) >
  class ConstantWeightFunction : public WeightFunctionBase< ConstantWeightFunction< X, W, T >, X, W, T > {

    /* friend declarations */

    friend class WeightFunctionBase< ConstantWeightFunction< X, W, T >, X, W, T >;

    /* type aliases */

    using Parent = WeightFunctionBase< ConstantWeightFunction< X, W, T >, X, W, T >;

    /* fields */

    W constant_;

    /* interface implementation functions */

    /**
     *  @brief Evaluate the weight function
     */
    W evaluate( const X& ) const noexcept {

      return this->constant();
    }

    /**
     *  @brief Calculate the integral of the weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< W >() ) >
    I calculateIntegral( const X& xLeft, const X& xRight ) const {

      return integration::histogram( xLeft, xRight, this->constant(), this->constant() );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using histogram interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateHistogramIntegral( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::histogram( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-lin interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLinearIntegral( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::linlin( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-log interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLogarithmicIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::linlog( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-lin interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLinearIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::loglin( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-log interpolation
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the left y-value of the tabulated function
     *  @param yRight   the right y-value of the tabulated function
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLogarithmicIntegral( const X& xLeft, const X& xRight,
                                               const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::loglog( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using Coulomb penetrability interpolation
     *
     *  @param xLeft       the left boundary of the panel
     *  @param xRight      the right boundary of the panel
     *  @param yLeft       the tabulated function value at the left boundary of the panel
     *  @param yRight      the tabulated function value at the right boundary of the panel
     *  @param threshold   the reaction threshold
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateCoulombPenetrabilityIntegral( const X& xLeft, const X& xRight,
                                             const Y& yLeft, const Y& yRight,
                                             const X& threshold ) const {

      return this->constant() * integration::coulomb( xLeft, xRight, yLeft, yRight, threshold,
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
     *  @param constant    the constant value of the weight function (default 1)
     *  @param tolerance   the targeted numerical integration tolerance (default 1e-8)
     */
    ConstantWeightFunction( W constant = W( 1 ), T tolerance = T( 1e-8 ) ) :
      Parent( std::move( tolerance ) ),
      constant_( std::move( constant ) ) {}

    /* methods */

    /**
     *  @brief Return the constant value
     */
    const W& constant() const noexcept {

      return this->constant_;
    }

    using Parent::tolerance;
    using Parent::operator();
    using Parent::integral;
    using Parent::integrateHistogram;
    using Parent::integrateLinearLinear;
    using Parent::integrateLinearLogarithmic;
    using Parent::integrateLogarithmicLinear;
    using Parent::integrateLogarithmicLogarithmic;
    using Parent::integrateCoulombPenetrability;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

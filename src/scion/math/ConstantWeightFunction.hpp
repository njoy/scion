#ifndef NJOY_SCION_MATH_CONSTANTWEIGHTFUNCTION
#define NJOY_SCION_MATH_CONSTANTWEIGHTFUNCTION

// system includes

// other includes
#include "scion/math/WeightFunctionBase.hpp"
#include "scion/math/OpenDomain.hpp"
#include "scion/integration.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A weight function w(x) = c
   */
  template < typename X, typename Y, typename W >
  class ConstantWeightFunction : public WeightFunctionBase< ConstantWeightFunction< X, Y, W >, X, Y, W > {

    /* friend declarations */
    friend class WeightFunctionBase< ConstantWeightFunction< X, Y, W >, X, Y, W >;
    friend class OneDimensionalFunctionBase< ConstantWeightFunction< X, Y, W >, X, W >;

    /* type aliases */
    using Parent = WeightFunctionBase< ConstantWeightFunction< X, Y, W >, X, Y, W >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  private:

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
     *  @brief Calculate the integral of weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< W >() ) >
    I calculateIntegral( const X& xLeft, const X& xRight ) const noexcept {

      return integration::histogram( xLeft, xRight, this->constant(), this->constant() );
    }

    /**
     *  @brief Calculate the mean of weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< W >() ) >
    I calculateMean( const X& xLeft, const X& xRight ) const noexcept {

      return integration::histogramMean( xLeft, xRight, this->constant(), this->constant() );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using histogram interpolation
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateHistogramIntegral( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const noexcept {

      return this->constant() * integration::histogram( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-lin interpolation
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLinearIntegral( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight ) const noexcept {

      return this->constant() * integration::linlin( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-log interpolation
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLogarithmicIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const noexcept {

      return this->constant() * integration::linlog( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-lin interpolation
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLinearIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::loglin( xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-log interpolation
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLogarithmicIntegral( const X& xLeft, const X& xRight,
                                               const Y& yLeft, const Y& yRight ) const {

      return this->constant() * integration::loglog( xLeft, xRight, yLeft, yRight );
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param constant  the constant value of the weight function
     */
    ConstantWeightFunction( W constant = 1. ) :
      Parent( OpenDomain< X >() ),
      constant_( std::move( constant ) ) {}

    /* methods */

    /**
     *  @brief Return the constant value
     */
    const W& constant() const noexcept {

      return this->constant_;
    }

    using Parent::integral;
    using Parent::mean;
    using Parent::integrateHistogram;
    using Parent::integrateLinearLinear;
    using Parent::integrateLinearLogarithmic;
    using Parent::integrateLogarithmicLinear;
    using Parent::integrateLogarithmicLogarithmic;
    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

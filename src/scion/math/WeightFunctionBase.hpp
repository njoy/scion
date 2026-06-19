#ifndef NJOY_SCION_MATH_WEIGHTFUNCTIONBASE
#define NJOY_SCION_MATH_WEIGHTFUNCTIONBASE

// system includes

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for an analytical weight function w(x)
   *
   *  This base class provides the interface for analytical weight functions used in
   *  integration of tabulated data. Weight functions can be used to calculate
   *  integrals of the form w(x) f(x) dx where f(x) is tabulated data.
   */
  template < typename Derived, typename X, typename W >
  class WeightFunctionBase : public OneDimensionalFunctionBase< Derived, X, W > {

    /* type aliases */

    using Parent = OneDimensionalFunctionBase< Derived, X, W >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  protected:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param domain   the domain of the weight function
     */
    WeightFunctionBase( DomainVariant domain ) :
      Parent( std::move( domain ) ) {}

    WeightFunctionBase() = default;
    WeightFunctionBase( const WeightFunctionBase& ) = default;
    WeightFunctionBase( WeightFunctionBase&& ) = default;

    WeightFunctionBase& operator=( const WeightFunctionBase& ) = default;
    WeightFunctionBase& operator=( WeightFunctionBase&& ) = default;

  public:

    /* methods */

    /**
     *  @brief Calculate the integral of the weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< W >() ) >
    I integral( const X& xLeft, const X& xRight ) const {

      return static_cast< const Derived* >( this )->calculateIntegral( xLeft, xRight );
    }

    /**
     *  @brief Calculate the mean of the weight function over a panel
     *
     *  The mean or first raw moment is defined as the integral of x * f(x)
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< W >() ) >
    I mean( const X& xLeft, const X& xRight ) const {

      return static_cast< const Derived* >( this )->calculateMean( xLeft, xRight );
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
    I integrateHistogram( const X& xLeft, const X& xRight,
                          const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->calculateHistogramIntegral( xLeft, xRight, yLeft, yRight );
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
    I integrateLinearLinear( const X& xLeft, const X& xRight,
                             const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->calculateLinearLinearIntegral( xLeft, xRight, yLeft, yRight );
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
    I integrateLinearLogarithmic( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->calculateLinearLogarithmicIntegral( xLeft, xRight, yLeft, yRight );
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
    I integrateLogarithmicLinear( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->calculateLogarithmicLinearIntegral( xLeft, xRight, yLeft, yRight );
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
    I integrateLogarithmicLogarithmic( const X& xLeft, const X& xRight,
                                       const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->calculateLogarithmicLogarithmicIntegral( xLeft, xRight, yLeft, yRight );
    }

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

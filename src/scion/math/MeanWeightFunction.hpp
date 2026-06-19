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
   */
  template < typename X, typename W >
  class MeanWeightFunction : public WeightFunctionBase< MeanWeightFunction< X, W >, X, W > {

    /* friend declarations */
    friend class WeightFunctionBase< MeanWeightFunction< X, W >, X, W >;
    friend class OneDimensionalFunctionBase< MeanWeightFunction< X, W >, X, W >;

    /* type aliases */
    using Parent = WeightFunctionBase< MeanWeightFunction< X, W >, X, W >;

  public:

    /* type aliases */

  private:

    /* fields */

    /* interface implementation functions */

    /**
     *  @brief Evaluate the weight function
     */
    W evaluate( const X& x ) const noexcept {

      return x;
    }

    /**
     *  @brief Calculate the integral of weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< W >() ) >
    I calculateIntegral( const X& xLeft, const X& xRight ) const noexcept {

      return integration::linlin( xLeft, xRight, xLeft, xRight );
    }

    /**
     *  @brief Calculate the mean of weight function over a panel
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< W >() ) >
    I calculateMean( const X& xLeft, const X& xRight ) const noexcept {

      return integration::linLinMean( xLeft, xRight, xLeft, xRight );
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
                                  const Y& yLeft, const Y& yRight ) const noexcept {

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
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLinearIntegral( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight ) const noexcept {

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
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLogarithmicIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const noexcept {

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
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
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
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLogarithmicIntegral( const X& xLeft, const X& xRight,
                                               const Y& yLeft, const Y& yRight ) const {

      return integration::logLogMean( xLeft, xRight, yLeft, yRight );
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     */
    MeanWeightFunction() : Parent( OpenDomain< X >() ) {}

    /* methods */

    using Parent::operator();
    using Parent::integral;
    using Parent::mean;
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

#ifndef NJOY_SCION_MATH_WEIGHTFUNCTIONBASE
#define NJOY_SCION_MATH_WEIGHTFUNCTIONBASE

// system includes
#include <utility>

// other includes
#include "scion/interpolation/Histogram.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"
#include "scion/interpolation/CoulombPenetrability.hpp"
#include "scion/integration/AdaptiveGaussLobatto.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for a weight function w(x)
   *
   *  This base class provides the interface for analytical weight functions used in
   *  integration of tabulated data. Weight functions can be used to calculate
   *  integrals of the form w(x) f(x) dx where f(x) is tabulated data.
   *
   *  Any class deriving from this base class must implement an evaluate() and can
   *  implement calculateIntegral(), calculateHistogramIntegral(),
   *  calculateLinearLinearIntegral(), calculateLinearLogarithmicIntegral(),
   *  calculateLogarithmicLinearIntegral(), calculateLogarithmicLogarithmicIntegral()
   *  and calculateCoulombPenetrabilityIntegral() function. If the derived class does
   *  not implement these, they will default to numerical integration using adaptive
   *  Gauss-Lobatto.
   */
  template < typename Derived, typename X, typename W,
             typename T = decltype( std::declval< X >() / std::declval< X >() ) >
  class WeightFunctionBase {

    /* fields */

    T tolerance_;

  protected:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param tolerance   the targeted numerical integration tolerance (default 1e-8)
     */
    WeightFunctionBase( T tolerance = T( 1e-8 ) ) :
      tolerance_( std::move( tolerance ) ) {}

    WeightFunctionBase( const WeightFunctionBase& ) = default;
    WeightFunctionBase( WeightFunctionBase&& ) = default;

    WeightFunctionBase& operator=( const WeightFunctionBase& ) = default;
    WeightFunctionBase& operator=( WeightFunctionBase&& ) = default;

    /* default implementation for imposed interface functions */

    /**
     *  @brief Calculate the integral of the weight function over a panel
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     */
    template < typename I = decltype( std::declval< X >() * std::declval< W >() ) >
    I calculateIntegral( const X& xLeft, const X& xRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        integration::AdaptiveGaussLobatto< X, W > integrator;
        auto functor = [&] ( const X& x ) { return this->operator()( x ); };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using histogram interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateHistogramIntegral( const X& xLeft, const X& xRight,
                                  const Y& yLeft, const Y& yRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::histogram( x, xLeft, xRight, yLeft, yRight );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-lin interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLinearIntegral( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::linlin( x, xLeft, xRight, yLeft, yRight );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using lin-log interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLinearLogarithmicIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::linlog( x, xLeft, xRight, yLeft, yRight );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-lin interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the tabulated function value at the left boundary of the panel
     *  @param yRight   the tabulated function value at the right boundary of the panel
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLinearIntegral( const X& xLeft, const X& xRight,
                                          const Y& yLeft, const Y& yRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::loglin( x, xLeft, xRight, yLeft, yRight );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using log-log interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
     *
     *  @param xLeft    the left boundary of the panel
     *  @param xRight   the right boundary of the panel
     *  @param yLeft    the left y-value of the tabulated function
     *  @param yRight   the right y-value of the tabulated function
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I calculateLogarithmicLogarithmicIntegral( const X& xLeft, const X& xRight,
                                               const Y& yLeft, const Y& yRight ) const {

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::loglog( x, xLeft, xRight, yLeft, yRight );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

    /**
     *  @brief Integrate w(x) * f(x) over a panel using Coulomb penetrability interpolation
     *
     *  This is the default implementation that uses adaptive Gauss-Lobatto
     *  quadrature. Omitting the implementation of this function in the derived
     *  class will lead to this function to be called instead.
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

      if ( xLeft == xRight ) {

        return I( 0 );
      }
      else {

        using F = decltype( std::declval< Y >() * std::declval< W >() );
        integration::AdaptiveGaussLobatto< X, F > integrator;
        auto functor = [&] ( const X& x ) {

          return this->operator()( x ) * interpolation::coulomb( x, xLeft, xRight, yLeft, yRight, threshold );
        };
        return integrator( functor, xLeft, xRight, this->tolerance() );
      }
    }

  public:

    /* type aliases */

    using XType = X;
    using YType = W;

    /* methods */

    /**
     *  @brief Return the targeted numerical integration tolerance
     */
    const T& tolerance() const noexcept {

      return this->tolerance_;
    }

    /**
     *  @brief Evaluate the weight function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    W operator()( const X& x ) const {

      return static_cast< const Derived* >( this )->evaluate( x );
    }

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

    /**
     *  @brief Integrate w(x) * f(x) over a panel using CoulombPenetrability interpolation
     *
     *  @param xLeft       the left boundary of the panel
     *  @param xRight      the right boundary of the panel
     *  @param yLeft       the tabulated function value at the left boundary of the panel
     *  @param yRight      the tabulated function value at the right boundary of the panel
     *  @param threshold   the reaction threshold
     */
    template < typename Y, typename I = decltype( std::declval< X >() * std::declval< Y >() * std::declval< W >() ) >
    I integrateCoulombPenetrability( const X& xLeft, const X& xRight,
                                     const Y& yLeft, const Y& yRight,
                                     const X& threshold ) const {

      return static_cast< const Derived* >( this )->calculateCoulombPenetrabilityIntegral( xLeft, xRight, yLeft, yRight, threshold );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_MATH_POLYNOMIALSERIES
#define NJOY_SCION_MATH_POLYNOMIALSERIES

// system includes
#include <cmath>
#include <limits>
#include <vector>

// other includes
#include "scion/math/horner.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/SeriesBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A polynomial function y -> f(x) = sum c_i x^i of order n
   *
   *  This class represents a polynomial function y -> f(x) = sum c_i x^i of
   *  order n defined over a domain. The domain can be any specified interval [a,b]
   *  or an open domain (+/-infinity).
   *
   *  The horner scheme is used for the evaluation of the series.
   *
   *  The first order derivative of a polynomial series is another polynomial
   *  series: y -> d/dx f(x) = sum i c_i x^(i-1) for i = 1 to n
   *
   *  The primitive or antiderivative of a polynomial series is another polynomial
   *  series: y -> int[left,x] f(x) dx = c_0 + sum c_i/(i+1) x^(i+1)
   *  The integrated series is defined so that the integral function for x = left
   *  equals 0.
   *
   *  The derivative and primitive function is defined over the same domain as
   *  the original series.
   */
  template < typename X, typename Y >
  class PolynomialSeries : public SeriesBase< PolynomialSeries< X, Y >, X, Y > {

    /* friend declarations */

    friend class SeriesBase< PolynomialSeries< X, Y >, X, Y >;
    friend class OneDimensionalFunctionBase< PolynomialSeries< X, Y >, X, Y >;

    /* type aliases */

    using Parent = SeriesBase< PolynomialSeries< X, Y >, X, Y >;

    /* fields */

    X lower_;
    X upper_;

    /* auxiliary functions */

    static void verifyDomain( const X& lower, const X& upper ) {

      if ( ! ( lower < upper ) ) {

        Log::error( "Incoherent domain for a polynomial series, expected lower < upper" );
        Log::info( "Lower limit: {}", lower );
        Log::info( "Upper limit: {}", upper );
        throw std::exception();
      }
    }

    void verifyFiniteDomain() const {

      if ( ! std::isfinite( this->lower() ) || ! std::isfinite( this->upper() ) ) {

        Log::error( "Cannot integrate a polynomial series defined over an infinite domain" );
        Log::info( "Lower limit: {}", this->lower() );
        Log::info( "Upper limit: {}", this->upper() );
        throw std::exception();
      }
    }

    /* interface implementation functions */

    /**
     *  @brief Return the lower limit of the domain
     */
    const X& lower() const noexcept {

      return this->lower_;
    }

    /**
     *  @brief Return the upper limit of the domain
     */
    const X& upper() const noexcept {

      return this->upper_;
    }

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return math::horner( this->coefficients(), x );
    }

    /**
     *  @brief Return the derivative of the polynomial series
     *
     *  The first order derivative of a polynomial series is another polynomial
     *  series: y -> d/dx f(x) = sum i c_i x^(i-1) for i = 1 to n
     *
     *  The derivative function is defined over the same domain as the
     *  original function.
     */
    PolynomialSeries calculateDerivative() const {

      const std::size_t order = this->order();
      std::vector< Y > derivative( order != 0 ? order : 1, Y( 0. ) );
      for ( std::size_t i = 0; i < order; ++i ) {

        derivative[i] = ( i + 1 ) * this->coefficients()[i + 1];
      }

      return PolynomialSeries( this->lower(), this->upper(), std::move( derivative ) );
    }

    /**
     *  @brief Return the primitive (or antiderivative) of the polynomial series
     *
     *  The primitive or antiderivative of a polynomial series is another polynomial
     *  series: y -> int f(x) = c_0 + sum c_i/(i+1) x^(i+1)
     *
     *  The integrated series is defined so that the integral function for x = left
     *  equals 0.
     *
     *  The primitive function is defined over the same domain as the original
     *  series.
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    PolynomialSeries calculatePrimitive( const X& left = X( 0. ) ) const {

      std::size_t order = this->order();
      std::vector< Y > primitive( order + 2, Y( 0. ) );
      for ( std::size_t i = 1; i < order + 2; ++i ) {

        primitive[i] = this->coefficients()[i-1] / Y( i );
      }
      primitive[0] -= horner( primitive, left );

      return PolynomialSeries( this->lower(), this->upper(), std::move( primitive ) );
    }

    /**
     *  @brief Calculate the integral (zeroth order moment) of the series over its domain
     */
    auto calculateIntegral() const {

      this->verifyFiniteDomain();

      return this->primitive( this->lower() )( this->upper() );
    }

    /**
     *  @brief Calculate the unnormalised mean (first order raw moment) of the series over its domain
     */
    auto calculateMean() const {

      this->verifyFiniteDomain();

      auto coefficients = this->coefficients();
      coefficients.insert( coefficients.begin(), 0. );
      return PolynomialSeries( this->lower(), this->upper(),
                               std::move( coefficients ) ).primitive( this->lower() )( this->upper() );
    }

    /**
     *  @brief Return the coefficients for a product
     */
    std::vector< Y > calculateProduct( const std::vector< Y >& right ) const {

      //! @todo this migth be reimplemented using a cartesian product

      std::vector< Y > coefficients( this->order() + right.size() );
      for ( std::size_t i = 0; i < this->coefficients().size(); ++i ) {

        for ( std::size_t j = 0; j < right.size(); ++j ) {

          coefficients[ i + j ] += this->coefficients()[i] * right[j];
        }
      }
      return coefficients;
    }

    Matrix< Y > companionMatrix( const Y& a ) const {

      // This does not check for order 0 or 1: this case is explicitly handled in the
      // roots( ... ) method.

      const std::size_t order = this->order();
      const Y scale = this->coefficients().back();

      Matrix< X > matrix( order, order );
      matrix.setZero();

      matrix( order - 1, 0 ) = - ( this->coefficients()[0] - a ) / scale;
      matrix( 0, 1 ) = Y( 1. );
      for ( std::size_t i = 1; i < order; ++i ) {

        matrix( order - 1, i ) = - this->coefficients()[i] / scale;
        if ( i + 1 < order ) {

          matrix( i, i + 1 ) = Y( 1. );
        }
      }

      return matrix;
    }

    /* constructor */

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;

    /* constructor */

    PolynomialSeries() = default;

    PolynomialSeries( const PolynomialSeries& ) = default;
    PolynomialSeries( PolynomialSeries&& ) = default;

    PolynomialSeries& operator=( const PolynomialSeries& ) = default;
    PolynomialSeries& operator=( PolynomialSeries&& ) = default;

    /**
     *  @brief Assignment operator
     *
     *  @param coefficient   the zero order coefficient
     */
    PolynomialSeries& operator=( const Y& value ) {

      return Parent::operator=( value );
    }

    /**
     *  @brief Constructor
     *
     *  @param lower          the lower limit of the domain
     *  @param upper          the upper limit of the domain
     *  @param coefficients   the coefficients of the polynomial series (from
     *                        lowest to highest order coefficient)
     */
    PolynomialSeries( X lower, X upper, std::vector< Y > coefficients ) :
      Parent( std::move( coefficients ) ),
      lower_( std::move( lower ) ), upper_( std::move( upper ) ) {

      verifyDomain( this->lower(), this->upper() );
    }

    /**
     *  @brief Constructor
     *
     *  @param coefficients   the coefficients of the polynomial series (from
     *                        lowest to highest order coefficient)
     */
    PolynomialSeries( std::vector< Y > coefficients ) :
      PolynomialSeries( -std::numeric_limits< X >::infinity(),
                        std::numeric_limits< X >::infinity(),
                        std::move( coefficients ) ) {}

    /* methods */

    using Parent::coefficients;
    using Parent::order;
    using Parent::roots;
    using Parent::derivative;
    using Parent::primitive;
    using Parent::integral;
    using Parent::mean;
    using Parent::linearise;
    using Parent::operator+;
    using Parent::operator-;
    using Parent::operator*;
    using Parent::operator/;
    using Parent::operator+=;
    using Parent::operator-=;
    using Parent::operator*=;
    using Parent::operator/=;
    using Parent::operator==;
    using Parent::operator!=;
    using Parent::operator();
    using Parent::lowerLimit;
    using Parent::upperLimit;
    using Parent::isInside;
    using Parent::isContained;
  };

  /**
   *  @brief Scalar and series addition
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeries< X, Y >
  operator+( const S& left, const PolynomialSeries< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and series subtraction
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeries< X, Y >
  operator-( const S& left, const PolynomialSeries< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and series multiplication
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeries< X, Y >
  operator*( const S& left, const PolynomialSeries< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

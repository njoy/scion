#ifndef NJOY_SCION_MATH_LEGENDRESERIES
#define NJOY_SCION_MATH_LEGENDRESERIES

// system includes
#include <vector>

// other includes
#include "scion/math/clenshaw.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/SeriesBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A Legendre series function y -> f(x) = sum c_i P_i(x) of order n
   *
   *  This class represents a Legendre series function y -> f(x) =
   *  sum c_i P_i(x) defined over the domain [-1,1].
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series
   *  using the following recursion relation for Legendre polynomials:
   *    P_(n+1) = (2n+1)/(n+1) x P_n - n/(n+1) P_(n-1)
   *
   *  The derivative function of a Legendre series function is another
   *  Legendre series function. The coefficients of the new Legendre series
   *  are calculated using the derivative of a Legendre polynomial as a
   *  function of other Legendre polynomials:
   *    d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...
   *  knowing that:
   *    d/dx P_0 = 0.0
   *    d/dx P_1 = P_0
   *
   *  This formula can be derived using the following property of Legendre
   *  polynomials:
   *    ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)
   *
   *  The primitive or antiderivative of a Legendre series function is another
   *  Legendre series function. The coefficients of the new Legendre series
   *  are calculated using the integral of a Legendre polynomial as a
   *  function of other Legendre polynomials:
   *    int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
   *
   *  The integrated series is defined so that the integral function for x = left
   *  equals 0.
   *
   *  The derivative and primitive function is defined over the same domain as
   *  the original function.
   */
  template < typename X, typename Y = X >
  class LegendreSeries : public SeriesBase< LegendreSeries< X, Y >, X, Y > {

    /* friend declarations */

    friend class SeriesBase< LegendreSeries< X, Y >, X, Y >;
    friend class OneDimensionalFunctionBase< LegendreSeries< X, Y >, X, Y >;

    /* type aliases */

    using Parent = SeriesBase< LegendreSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary functions */

    /* interface implementation functions */

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  The Clenshaw recursion scheme is used for the evaluation of the series
     *  using the following recursion relation for Legendre polynomials:
     *
     *    P(n+2,x) = (2k+1)/(k+1) x P(n+1,x) - k/(k+1) P(n,x)
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return math::clenshawLegendre( this->coefficients(), x );
    }

    /**
     *  @brief Return the derivative of the Legendre series
     *
     *  The derivative function of a Legendre series function is another
     *  Legendre series function. The coefficients of the new Legendre series
     *  are calculated using the derivative of a Legendre polynomial as a
     *  function of other Legendre polynomials:
     *    d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...
     *  knowing that:
     *    d/dx P_0 = 0.0
     *    d/dx P_1 = P_0
     *
     *  This formula can be derived using the following property of Legendre
     *  polynomials:
     *    ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)
     *
     *  The derivative function is defined over the same domain as the
     *  original function.
     */
    LegendreSeries calculateDerivative() const {

      const unsigned int order = this->order();
      std::vector< Y > derivative( order, Y( 0. ) );
      for ( unsigned int i = 0; i < order; ++i ) {

        const Y a = this->coefficients()[i + 1];
        int j = static_cast< int >( i );
        while ( 0 <= j ) {

          derivative[j] += static_cast< Y >( 2 * j + 1 ) * a;
          j -= 2;
        }
      }

      return LegendreSeries( std::move( derivative ) );
    }

    /**
     *  @brief Return the primitive (or antiderivative) of the Legendre series
     *
     *  The primitive or antiderivative of a Legendre series function is another
     *  Legendre series function. The coefficients of the new Legendre series
     *  are calculated using the integral of a Legendre polynomial as a
     *  function of other Legendre polynomials:
     *    int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
     *
     *  The integrated series is defined so that the integral function for x = left
     *  equals 0.
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    LegendreSeries calculatePrimitive( const X& left = X( 0. ) ) const {

      unsigned int order = this->order();
      std::vector< Y > primitive( order + 2, Y( 0. ) );
      primitive[1] = this->coefficients()[0];
      for ( unsigned int i = 1; i < order + 1; ++i ) {

        auto c =  this->coefficients()[i] / Y( 2 * i + 1 );
        primitive[i + 1] += c;
        primitive[i - 1] -= c;
      }
      primitive[0] -= clenshawLegendre( primitive, left );

      return LegendreSeries( std::move( primitive ) );
    }

    /**
     *  @brief Calculate the integral (zeroth order moment) of the series over its domain
     */
    auto calculateIntegral() const {

      return X( 2. ) * this->coefficients().front();
    }

    /**
     *  @brief Calculate the unnormalised mean (first order raw moment) of the series over its domain
     */
    auto calculateMean() const {

      return this->order() == 0
             ? 0.
             : 2. * this->coefficients()[1] / 3.;
    }

    /**
     *  @brief Return the coefficients for a product
     */
    std::vector< Y > calculateProduct( const std::vector< Y >& ) const {

      Log::error( "Multiplication of Legendre polynomials is not implemented yet, "
                  "contact a developer." );
      throw std::exception();
    }

    Matrix< Y > companionMatrixBoyd( const Y& a ) const {

      // Reference:
      // John P. Boyd
      // Computing the zeros, maxima and inflection points of Chebyshev, Legendre
      // and Fourier series: solving transcendental equations by spectral
      // interpolation and polynomial rootfinding
      // Journal of Engineering Mathematics volume 56, pages 203–219 (2006)
      // doi: 10.1007/s10665-006-9087-5

      // This does not check for order 0 or 1: this case is explicitly handled in the
      // roots( ... ) method.

      const unsigned int order = this->order();
      const Y scale = this->coefficients().back() * Y( 2 * order - 1 ) / Y( order );

      Matrix< X > matrix( order, order );
      matrix.setZero();

      matrix( order - 1, 0 ) = - ( this->coefficients().front() - a ) / scale;
      matrix( 0, 1 ) = Y( 1. );
      for ( unsigned int i = 1; i < order - 1; ++i ) {

        matrix( i, i - 1 ) = Y( i ) / Y( 2 * i + 1 );
        matrix( i, i + 1 ) = Y( i + 1 ) / Y( 2 * i + 1 );
        matrix( order - 1, i ) = - this->coefficients()[i] / scale;
      }
      matrix( order - 1, order - 2 ) += Y( order - 1 ) / Y( 2 * order - 1 );
      matrix( order - 1, order - 1 ) = - this->coefficients()[order - 1] / scale;

      matrix.transposeInPlace();
      matrix.reverseInPlace();

      return matrix;
    }

    Matrix< Y > companionMatrix( const Y& a ) const {

      // Reference: numpy

      // This does not check for order 0 or 1: this case is explicitly handled in the
      // roots( ... ) method.

      const unsigned int order = this->order();
      const Y scale = this->coefficients().back() * Y( 2 * order - 1 ) / Y( order );

      Matrix< X > matrix( order, order );
      matrix.setZero();

      for ( unsigned int i = 0; i < order - 1; ++i ) {

        matrix( i, i + 1 ) = Y( i + 1 ) / std::sqrt( Y( 2 * i + 1 ) * Y( 2 * i + 3 ) );
        matrix( i + 1, i ) = matrix( i, i + 1 );
      }
      matrix( order - 1, order - 2 ) = matrix( order - 2, order - 1 );

      matrix( order - 1, 0 ) -= ( this->coefficients().front() - a ) / scale
                                * std::sqrt( Y( 2 * order - 1 ) );
      for ( unsigned int i = 1; i < order; ++i ) {

        matrix( order - 1, i ) -= this->coefficients()[i] / scale
                                  / std::sqrt( Y( 2 * i + 1 ) )
                                  * std::sqrt( Y( 2 * order - 1 ) );
      }

      matrix.transposeInPlace();
      matrix.reverseInPlace();

      return matrix;
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    LegendreSeries( Parent series ) : Parent( std::move( series ) ) {}

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    LegendreSeries() = default;

    LegendreSeries( const LegendreSeries& ) = default;
    LegendreSeries( LegendreSeries&& ) = default;

    LegendreSeries& operator=( const LegendreSeries& ) = default;
    LegendreSeries& operator=( LegendreSeries&& ) = default;

    /**
     *  @brief Assignment operator
     *
     *  @param coefficient   the zero order coefficient
     */
    LegendreSeries& operator=( const Y& value ) {

      return Parent::operator=( value );
    }

    /**
     *  @brief Constructor
     *
     *  @param coefficients   the coefficients of the Legendre series (from
     *                        lowest to highest order coefficient)
     */
    LegendreSeries( std::vector< Y > coefficients ) :
      Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

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
    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

  /**
   *  @brief Scalar and series addition
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  LegendreSeries< X, Y >
  operator+( const S& left, const LegendreSeries< X, Y >& right ) {

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
  LegendreSeries< X, Y >
  operator-( const S& left, const LegendreSeries< X, Y >& right ) {

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
  LegendreSeries< X, Y >
  operator*( const S& left, const LegendreSeries< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

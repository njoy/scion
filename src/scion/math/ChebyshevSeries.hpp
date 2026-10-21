#ifndef NJOY_SCION_MATH_CHEBYSHEVSERIES
#define NJOY_SCION_MATH_CHEBYSHEVSERIES

// system includes

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
   *  @brief A Chebyshev series function y -> f(x) = sum c_i T_i(x) of order n
   *
   *  This class represents a Chebyshev series function y -> f(x) =
   *  sum c_i T_i(x) defined over the domain [-1,1].
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series
   *  using the following recursion relation for Chebyshev polynomials:
   *    T_(n+1) = 2 x T_n - T_(n-1)
   *
   *  The derivative function of a Chebyshev series function is another
   *  Chebyshev series function. The coefficients of the new Chebyshev series
   *  are calculated using the derivative of a Chebyshev polynomial as a
   *  function of other Chebyshev polynomials:
   *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even
   *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd
   *  This relation can be proven by mathematical induction.
   *
   *  The primitive or antiderivative of a Chebyshev series function is another
   *  Chebyshev series function. The coefficients of the new Chebyshev series
   *  are calculated using the integral of a Chebyshev polynomial as a
   *  function of other Chebyshev polynomials:
   *    2 int T_n = T_(n + 1)/(n + 1) - T_(n - 1)/(n - 1)
   *
   *  The integrated series is defined so that the integral function for x = left
   *  equals 0.
   *
   *  The derivative  and primitive function is defined over the same domain as
   *  the original function.
   */
  template < typename X, typename Y >
  class ChebyshevSeries : public SeriesBase< ChebyshevSeries< X, Y >, X, Y > {

    /* friend declarations */

    friend class SeriesBase< ChebyshevSeries< X, Y >, X, Y >;
    friend class OneDimensionalFunctionBase< ChebyshevSeries< X, Y >, X, Y >;

    /* type aliases */

    using Parent = SeriesBase< ChebyshevSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary functions */

    /* interface implementation functions */

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  The Clenshaw recursion scheme is used for the evaluation of the series
     *  using the following recursion relation for Chebyshev polynomials:
     *
     *    T_(n+2) = 2 x T_(n+1) - T_n
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return math::clenshawChebyshev( this->coefficients(), x );
    }

    /**
     *  @brief Return the derivative of the Chebyshev series
     *
     *  The derivative function of a Chebyshev series function is another
     *  Chebyshev series function. The coefficients of the new Chebyshev series
     *  are calculated using the derivative of a Chebyshev polynomial as a
     *  function of other Chebyshev polynomials:
     *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even
     *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd
     *
     *  This relation can be proven by mathematical induction.
     *
     *  The derivative function is defined over the same domain as the
     *  original function.
     */
    ChebyshevSeries calculateDerivative() const {

      const unsigned int order = this->order();
      std::vector< Y > derivative( order, Y( 0. ) );
      for ( unsigned int i = 0; i < order; ++i ) {

        const Y a = static_cast< Y >( 2 * ( i + 1 ) ) * this->coefficients()[i + 1];
        int j = static_cast< int >( i );
        while ( 0 < j ) {

          derivative[j] += a;
          j -= 2;
        }
        if ( 0 == j ) {

          derivative[0] += static_cast< Y >( i + 1 ) * this->coefficients()[i + 1];
        }
      }

      return ChebyshevSeries( std::move( derivative ) );
    }

    /**
     *  @brief Return the primitive (or antiderivative) of the Chebyshev series
     *
     *  The primitive or antiderivative of a Chebyshev series function is another
     *  Chebyshev series function. The coefficients of the new Chebyshev series
     *  are calculated using the integral of a Chebyshev polynomial as a
     *  function of other Chebyshev polynomials:
     *    2 int T_n = T_(n + 1)/(n + 1) - T_(n - 1)/(n - 1)
     *
     *  The integrated series is defined so that the integral function for x = left
     *  equals 0.
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    ChebyshevSeries calculatePrimitive( const X& left = X( 0. ) ) const {

      unsigned int order = this->order();
      std::vector< Y > primitive( order + 2, Y( 0. ) );
      primitive[1] = this->coefficients()[0];
      primitive[2] = Y( 0.25 ) * this->coefficients()[1];
      for ( unsigned int i = 2; i < order + 1; ++i ) {

        auto c =  Y( 0.5 ) * this->coefficients()[i];
        primitive[i + 1] += c / Y( i + 1 );
        primitive[i - 1] -= c / Y( i - 1 );
      }
      primitive[0] -= clenshawChebyshev( primitive, left );

      return ChebyshevSeries( std::move( primitive ) );
    }

    /**
     *  @brief Calculate the integral (zeroth order moment) of the series over its domain
     */
    auto calculateIntegral() const {

      // integral of T(n,x) between -1 and 1 is ( -1^n + 1 ) / ( 1 - n^2 ) for even n
      // integral of T(n,x) between -1 and 1 is 0 for odd n

      auto result = 2. * this->coefficients().front();
      for ( unsigned int i = 2; i < this->coefficients().size(); i += 2 ) {

        result += 2. * this->coefficients()[i] / ( 1. - i * i );
      }
      return result;
    }

    /**
     *  @brief Calculate the unnormalised mean (first order raw moment) of the series over its domain
     */
    auto calculateMean() const {

      if ( this->order() == 0 ) {

        return 0.;
      }
      else {

        // x T(0,x) = T(1,x)
        // x T(m,x) = ( T(m+1,x) + T(m-1,x) ) / 2 for m > 0
        // integral of T(n,x) between -1 and 1 is ( -1^n + 1 ) / ( 1 - n^2 ) for even n
        // integral of T(n,x) between -1 and 1 is 0 for odd n
        auto result = 2. * this->coefficients()[1] / 3.;
        for ( unsigned int i = 3; i < this->coefficients().size(); i += 2 ) {

          auto a = i + 1;
          auto b = i - 1;
          result += this->coefficients()[i] * ( 1. / ( 1. - a * a ) + 1. / ( 1. - b * b ) );
        }
        return result;
      }
    }

    /**
     *  @brief Return the coefficients for a product
     *
     *  Chebyshev polynomials satisfy the following relation:
     *    T(n,x) T(m,x) = ( T(n+m,x) + T(abs(n-m),x) ) / 2 for n,m > 0
     */
    std::vector< Y > calculateProduct( const std::vector< Y >& right ) const {

      //! @todo this migth be reimplemented using a cartesian product

      std::vector< Y > coefficients( this->order() + right.size() );
      Y half( 0.5 );
      for ( unsigned int i = 0; i < this->coefficients().size(); ++i ) {

        for ( unsigned int j = 0; j < right.size(); ++j ) {

          auto product = half * this->coefficients()[i] * right[j];
          coefficients[ i + j ] += product;
          coefficients[ j > i ? j - i : i - j ] += product;
        }
      }
      return coefficients;
    }

    Matrix< Y > companionMatrixBoyd( const Y& a ) const {

      // Reference:
      // John P. Boyd
      // Computing the zeros, maxima and inflection points of Chebyshev, Legendre
      // and Fourier series: solving transcendental equations by spectral
      // interpolation and polynomial rootfinding
      // Journal of Engineering Mathematics volume 56, pages 203–219 (2006)
      // doi: 10.1007/s10665-006-9087-5

      // This does not check for order 0: this case is explicitly handled in the
      // roots( ... ) method.

      const unsigned int order = this->order();
      const Y scale = this->coefficients().back() * Y( 2 );

      Matrix< X > matrix( order, order );
      matrix.setZero();

      matrix( order - 1, 0 ) = - ( this->coefficients()[0] - a ) / scale;
      matrix( 0, 1 ) = Y( 1. );
      for ( unsigned int i = 1; i < order - 1; ++i ) {

        matrix( i, i - 1 ) = Y( 0.5 );
        matrix( i, i + 1 ) = Y( 0.5 );
        matrix( order - 1, i ) = - this->coefficients()[i] / scale;
      }
      matrix( order - 1, order - 2 ) += Y( 0.5 );
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
      const Y scale = this->coefficients().back() * Y( 2 );

      Matrix< X > matrix( order, order );
      matrix.setZero();

      matrix( 0, 1 ) = std::sqrt( Y( 0.5 ) );
      matrix( 1, 0 ) = matrix( 0, 1 );
      for ( unsigned int i = 1; i < order - 1; ++i ) {

        matrix( i, i + 1 ) = Y( 0.5 );
        matrix( i + 1, i ) = matrix( i, i + 1 );
      }
      matrix( order - 1, order - 2 ) = matrix( order - 2, order - 1 );

      matrix( order - 1, 0 ) -= ( this->coefficients().front() - a ) / scale
                                * std::sqrt( Y( 2. ) );
      for ( unsigned int i = 1; i < order; ++i ) {

        matrix( order - 1, i ) -= this->coefficients()[i] / scale;
      }

      matrix.transposeInPlace();
      matrix.reverseInPlace();

      return matrix;
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    ChebyshevSeries( Parent series ) : Parent( std::move( series ) ) {}

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ChebyshevSeries() = default;

    ChebyshevSeries( const ChebyshevSeries& ) = default;
    ChebyshevSeries( ChebyshevSeries&& ) = default;

    ChebyshevSeries& operator=( const ChebyshevSeries& ) = default;
    ChebyshevSeries& operator=( ChebyshevSeries&& ) = default;

    /**
     *  @brief Assignment operator
     *
     *  @param coefficient   the zero order coefficient
     */
    ChebyshevSeries& operator=( const Y& value ) {

      return Parent::operator=( value );
    }

    /**
     *  @brief Constructor
     *
     *  @param coefficients   the coefficients of the Chebyshev series (from
     *                        lowest to highest order coefficient)
     */
    ChebyshevSeries( std::vector< Y > coefficients ) :
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
  ChebyshevSeries< X, Y >
  operator+( const S& left, const ChebyshevSeries< X, Y >& right ) {

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
  ChebyshevSeries< X, Y >
  operator-( const S& left, const ChebyshevSeries< X, Y >& right ) {

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
  ChebyshevSeries< X, Y >
  operator*( const S& left, const ChebyshevSeries< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

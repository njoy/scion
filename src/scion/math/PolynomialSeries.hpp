#ifndef NJOY_SCION_MATH_POLYNOMIALSERIES
#define NJOY_SCION_MATH_POLYNOMIALSERIES

// system includes
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
   *  order n defined over a domain. Currently, the domain can either be the
   *  open domain where every value of x is allowed or the interval domain that
   *  restricts x to an interval [a,b].
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

    /* auxiliary functions */

    /* interface implementation functions */

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

      std::vector< Y > derivative = this->coefficients();
      for ( unsigned int i = 1; i < derivative.size(); ++i ) {

        derivative[i] *= i;
      }
      derivative.erase( derivative.begin() );

      return PolynomialSeries( this->domain(), std::move( derivative ) );
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

      unsigned int order = this->order();
      std::vector< Y > primitive( order + 2, Y( 0. ) );
      for ( unsigned int i = 1; i < order + 2; ++i ) {

        primitive[i] = this->coefficients()[i-1] / Y( i );
      }
      primitive[0] -= horner( primitive, left );

      return PolynomialSeries( this->domain(), std::move( primitive ) );
    }

    /**
     *  @brief Calculate the integral (zeroth order moment) of the series over its domain
     */
    auto calculateIntegral() const {

      if ( std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

        auto lower = std::get< IntervalDomain< X > >( this->domain() ).lowerLimit();
        auto upper = std::get< IntervalDomain< X > >( this->domain() ).upperLimit();
        return this->primitive( lower )( upper );
      }
      else {

        Log::error( "Cannot calculate the integral of a polynomial series with an open domain" );
        throw std::exception();
      }
    }

    /**
     *  @brief Calculate the unnormalised mean (first order raw moment) of the series over its domain
     */
    auto calculateMean() const {

      if ( std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

        auto lower = std::get< IntervalDomain< X > >( this->domain() ).lowerLimit();
        auto upper = std::get< IntervalDomain< X > >( this->domain() ).upperLimit();

        auto coefficients = this->coefficients();
        coefficients.insert( coefficients.begin(), 0. );
        return PolynomialSeries( this->domain(), std::move( coefficients ) ).primitive( lower )( upper );
      }
      else {

        Log::error( "Cannot calculate the integral of a polynomial series with an open domain" );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the coefficients for a product
     */
    std::vector< Y > calculateProduct( const std::vector< Y >& right ) const {

      //! @todo this migth be reimplemented using a cartesian product

      std::vector< Y > coefficients( this->order() + right.size() );
      for ( unsigned int i = 0; i < this->coefficients().size(); ++i ) {

        for ( unsigned int j = 0; j < right.size(); ++j ) {

          coefficients[ i + j ] += this->coefficients()[i] * right[j];
        }
      }
      return coefficients;
    }

    Matrix< Y > companionMatrix( const Y& a ) const {

      // This does not check for order 0 or 1: this case is explicitly handled in the
      // roots( ... ) method.

      const unsigned int order = this->order();
      const Y scale = this->coefficients().back();

      Matrix< X > matrix( order, order );
      matrix.setZero();

      matrix( order - 1, 0 ) = - ( this->coefficients()[0] - a ) / scale;
      matrix( 0, 1 ) = Y( 1. );
      for ( unsigned int i = 1; i < order; ++i ) {

        matrix( order - 1, i ) = - this->coefficients()[i] / scale;
        if ( i + 1 < order ) {

          matrix( i, i + 1 ) = Y( 1. );
        }
      }

      return matrix;
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    PolynomialSeries( Parent series ) : Parent( std::move( series ) ) {}

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
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
     *  @param domain         the domain of the polynomial series
     *  @param coefficients   the coefficients of the polynomial series
     *                        (from lowest to highest order coefficient)
     */
    PolynomialSeries( DomainVariant domain, std::vector< Y > coefficients ) :
      Parent( std::move( domain ), std::move( coefficients ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param coefficients   the coefficients of the polynomial series (from
     *                        lowest to highest order coefficient)
     */
    PolynomialSeries( std::vector< Y > coefficients ) :
      PolynomialSeries( OpenDomain< X >(), std::move( coefficients ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param lower          the lower limit of the domain
     *  @param upper          the upper limit of the domain
     *  @param coefficients   the coefficients of the polynomial series (from
     *                        lowest to highest order coefficient)
     */
    PolynomialSeries( X lower, X upper, std::vector< Y > coefficients ) :
      PolynomialSeries( IntervalDomain< X >( std::move( lower ), std::move( upper ) ),
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

#ifndef NJOY_SCION_MATH_CHEBYSHEVAPPROXIMATION
#define NJOY_SCION_MATH_CHEBYSHEVAPPROXIMATION

// system includes
#include <vector>

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/ChebyshevSeries.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Approximation of a function f(x) in the [a,b] domain using a
   *         Chebyshev series
   *
   *  Users should note that the underlying Chebyshev series is ALWAYS defined in
   *  [-1, 1] and that the approximated function is defined on [a,b] and that
   *  a domain transformation is required to go from one to the other. This
   *  transformation is performed inside this object.
   *
   *  Chebyshev function approximation only works well within the defined
   *  domain. Outside of the domain, the approximated function can quickly diverge.
   *  Range checking by the user is advised.
   *
   *  The derivative function of an approximated function is another approximated
   *  function. The derivative is equal to the derivative of the underlying
   *  Chebyshev series and is defined over the same domain as the original
   *  approximated function.
   *
   *  The primitive of an approximated function is another approximated
   *  function. The primitive is equal to the primitive of the underlying
   *  Chebyshev series and is defined over the same domain as the original
   *  approximated function.
   *
   *  The integral function is defined so that the integral function for x = left
   *  equals 0.
   */
  template < typename X, typename Y >
  class ChebyshevApproximation :
      public OneDimensionalFunctionBase< ChebyshevApproximation< X, Y >, X, Y > {

    /* type aliases */

    using Parent = OneDimensionalFunctionBase< ChebyshevApproximation< X, Y >, X, Y >;

    /* fields */

    X lower_;
    X upper_;
    ChebyshevSeries< X, Y > series_;

    /* auxiliary function */

    template < typename Functor > static std::vector< Y >
    calculateCoefficients( X lower, X upper, Functor&& function, unsigned int order ) {

      std::vector< Y > coefficients( order + 1, Y( 0. ) );
      unsigned int n = order + 1;
      const double pi = std::acos( -1. );

      // transform x in [-1, 1] to x' in [lower, upper]
      const auto transform = [lower, upper] ( const X& x ) {

        return ( x + X( 1 ) ) * ( upper - lower ) / X( 2 ) + lower;
      };

      // calculate values of function in zeros of Chebyshev polynomial of order n
      std::vector< Y > f;
      for ( unsigned int i = 0; i < n; ++i ) {

        f.emplace_back( function( transform( std::cos( pi * ( i + 0.5 ) / n ) ) ) );
      }

      // calculate the coefficients of the approximation
      for ( unsigned int i = 0; i < n; ++i ) {

        for ( unsigned int j = 0; j < n; ++j ) {

          coefficients[i] += f[j] * std::cos( pi * i * ( j + 0.5 ) / n );
        }
        coefficients[i] *= 2. / Y( n );
      }
      coefficients[0] *= 0.5;

      return coefficients;
    }

    /**
     *  @brief Transform x in [a, b] to xprime in [-1, 1]
     *
     *  @param[in] x    the value of x to transform into xprime
     */
    X transform( const X& x ) const {

      return ( 2. * x - ( this->upper_ + this->lower_ ) )
             / ( this->upper_ - this->lower_ );
    }

    /**
     *  @brief Transform xprime in [-1, 1] to x in [a, b]
     *
     *  @param[in] xprime    the value of xprime to transform into x
     */
    X invert( const X& xprime ) const {

      return ( xprime + X( 1 ) ) * ( this->upper_ - this->lower_ ) / X( 2 ) + this->lower_;
    }

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ChebyshevApproximation() = default;

    /**
     *  @brief Constructor
     *
     *  @param domain      the domain of the approximated function
     *  @param series      the Chebyshev series that approximates the function
     */
    ChebyshevApproximation( IntervalDomain< X > domain,
                            ChebyshevSeries< X, Y > series ) :
      Parent( std::move( domain ) ),
      lower_( domain.lowerLimit() ), upper_( domain.upperLimit() ),
      series_( std::move( series ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param lower           the lower limit of the domain
     *  @param upper           the upper limit of the domain
     *  @param coefficients    the coefficients that approximate the function
     */
    ChebyshevApproximation( X lower, X upper, std::vector< Y > coefficients ) :
      ChebyshevApproximation( IntervalDomain( lower, upper ),
                              ChebyshevSeries< X, Y >( std::move( coefficients ) ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param lower       the lower limit of the domain
     *  @param upper       the upper limit of the domain
     *  @param function    the function to be approximated
     *  @param order       the order of the approximation
     */
    template < typename Functor >
    ChebyshevApproximation( X lower, X upper, Functor&& function, unsigned int order ) :
      ChebyshevApproximation(
          lower, upper,
          calculateCoefficients( lower, upper,
                                 std::forward< Functor >( function ), order ) ) {}

    /* interface implementation function */

    /**
     *  @brief Evaluate the approximated function for a value of x
     *
     *  Chebyshev function approximation only works well within the defined
     *  domain. Outside of the domain, the approximated function can quickly diverge.
     *  Range checking by the user is advised.
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return this->series_( this->transform( x ) );
    }

    /* methods */

    /**
     *  @brief Return the Chebyshev coefficients for the approximation
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->series_.coefficients();
    }

    /**
     *  @brief Return the Chebyshev order
     */
    unsigned int order() const noexcept {

      return this->series_.order();
    }

    /**
     *  @brief Return the derivative of the approximated function
     *
     *  The derivative function of an approximated function is another approximated
     *  function. The derivative is equal to the derivative of the underlying
     *  Chebyshev series and is defined over the same domain as the original
     *  approximated function.
     */
    ChebyshevApproximation derivative() const {

      return ChebyshevApproximation( IntervalDomain( this->lower_, this->upper_ ),
                                     this->series_.derivative() );
    }

    /**
     *  @brief Return the primitive (or antiderivative) of the approximated function
     *
     *  The primitive of an approximated function is another approximated
     *  function. The primitive is equal to the primitive of the underlying
     *  Chebyshev series and is defined over the same domain as the original
     *  approximated function.
     *
     *  The integral function is defined so that the integral function for x = left
     *  equals 0.
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    ChebyshevApproximation primitive( const X& left = X( 0. ) ) const {

      return ChebyshevApproximation( IntervalDomain( this->lower_, this->upper_ ),
                                     this->series_.primitive( left ) );
    }

    /**
     *  @brief Calculate the real roots of the approximated function so that f(x) = a
     *
     *  This function calculates all roots on the real axis of the approximated
     *  function as the roots of the underlying Chebyshev series.
     *
     *  @param[in] a   the value of a (default is zero)
     */
    std::vector< X > roots( const Y& a = Y( 0. ) ) const {

      auto roots = this->series_.roots( a );
      std::transform( roots.begin(), roots.end(), roots.begin(),
                      [this] ( auto&& x ) { return this->invert( x ); } );
      return roots;
    }

    /**
     *  @brief Linearise the approximated function and return an InterpolationTable
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    InterpolationTable< X, Y >
    linearise( Convergence&& convergence = Convergence() ) const {

      if ( 0 == this->order() ) {

        return InterpolationTable< X, Y >( { this->invert( -1. ),
                                             this->invert( +1. ) },
                                           { this->coefficients().front(),
                                             this->coefficients().front() } );
      }
      else if ( 1 == this->order() ) {

        const auto a = this->coefficients().back();
        const auto b = this->coefficients().front();
        return InterpolationTable< X, Y >( { this->invert( -1. ),
                                             this->invert( +1. ) },
                                           { b - a, b + a } );
      }
      else {

        // linearise the Chebyshev series
        auto linearised = this->series_.linearise( convergence );

        // transform the x values
        std::vector< X > x( linearised.numberPoints() );
        std::transform( linearised.x().cbegin(), linearised.x().cend(), x.begin(),
                        [this] ( const auto& value ) { return this->invert( value ); } );

        return InterpolationTable< X, Y >( std::move( x ),
                                           linearised.y() );
      }
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation& operator+=( const S& right ) {

      this->series_ += right;
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation& operator-=( const S& right ) {

      return this->operator+=( -right );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation& operator*=( const S& right ) {

      this->series_ *= right;
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation& operator/=( const S& right ) {

      return this->operator*=( Y( 1. ) / right );
    }

    /**
     *  @brief Approximation and scalar addition
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation operator+( const S& right ) const {

      ChebyshevApproximation result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief Approximation and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation operator-( const S& right ) const {

      ChebyshevApproximation result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief Approximation and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation operator*( const S& right ) const {

      ChebyshevApproximation result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief Approximation and scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    ChebyshevApproximation operator/( const S& right ) const {

      ChebyshevApproximation result = *this;
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    ChebyshevApproximation operator-() const {

      ChebyshevApproximation result = *this;
      result *= Y( -1. );
      return result;
    }

    /**
     *  @brief Inplace approximation addition
     *
     *  There is no domain checking on the two series. It is up to the user to
     *  verify that the domain of the two series are compatible.
     *
     *  @todo add domain check?
     *
     *  @param[in] right    the series
     */
    ChebyshevApproximation& operator+=( const ChebyshevApproximation& right ) {

      this->series_ += right.series_;
      return *this;
    }

    /**
     *  @brief Inplace approximation subtraction
     *
     *  There is no domain checking on the two series. It is up to the user to
     *  verify that the domain of the two series are compatible.
     *
     *  @todo add domain check?
     *
     *  @param[in] right    the series
     */
    ChebyshevApproximation& operator-=( const ChebyshevApproximation& right ) {

      this->series_ -= right.series_;
      return *this;
    }

    /**
     *  @brief Approximation and approximation addition
     *
     *  @param[in] right    the Series
     */
    ChebyshevApproximation operator+( const ChebyshevApproximation& right ) const {

      ChebyshevApproximation result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief Approximation and approximation subtraction
     *
     *  @param[in] right    the Series
     */
    ChebyshevApproximation operator-( const ChebyshevApproximation& right ) const {

      ChebyshevApproximation result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the series on the right hand side
     */
    bool operator==( const ChebyshevApproximation& right ) const noexcept {

      return this->domain() == right.domain() &&
             this->coefficients() == right.coefficients();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the series on the right hand side
     */
    bool operator!=( const ChebyshevApproximation& right ) const noexcept {

      return ! this->operator==( right );
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

  /**
   *  @brief Scalar and approximation addition
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the approximation
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  ChebyshevApproximation< X, Y >
  operator+( const S& left, const ChebyshevApproximation< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and approximation subtraction
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the approximation
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  ChebyshevApproximation< X, Y >
  operator-( const S& left, const ChebyshevApproximation< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and approximation multiplication
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the approximation
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  ChebyshevApproximation< X, Y >
  operator*( const S& left, const ChebyshevApproximation< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

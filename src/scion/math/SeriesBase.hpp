#ifndef NJOY_SCION_MATH_SERIESBASE
#define NJOY_SCION_MATH_SERIESBASE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/linearisation/grid.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/InterpolationTable.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/compare.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for series expansion objects
   *
   *  This base class provides the common interface for series expansions such
   *  as the polynomial series, Legendre series and Chebyshev series.
   */
  template < typename Derived, typename X, typename Y >
  class SeriesBase : public OneDimensionalFunctionBase< Derived, X, Y > {

    /* type aliases */

    using Parent = OneDimensionalFunctionBase< Derived, X, Y >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  private:

    /* fields */

    std::vector< Y > coefficients_;

    /* auxiliary function */

    static void verifyCoefficients( const std::vector< Y >& coefficients ) {

      if ( verification::isEmpty( coefficients ) ) {

        Log::error( "No coefficients defined for a series expansion" );
        throw std::exception();
      }
    }

    void trimCoefficients() {

      // this removes trailing zeros in the coefficients
      // if all coefficients are zero, it leaves a single order 0 coefficient
      // equal to zero

      if ( Y( 0. ) == this->coefficients().back() ) {

        const auto iter =
        std::find_if( this->coefficients().rbegin(), this->coefficients().rend(),
                      [] ( auto&& coefficient ) { return coefficient != Y( 0. ); } );
        this->coefficients_.erase( iter.base(), this->coefficients_.end() );
        if ( this->coefficients_.size() == 0 ) {

          this->coefficients_.push_back( Y( 0. ) );
        }
      }
    }

  protected:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    SeriesBase() = default;

    SeriesBase( const SeriesBase& ) = default;
    SeriesBase( SeriesBase&& ) = default;

    SeriesBase& operator=( const SeriesBase& ) = default;
    SeriesBase& operator=( SeriesBase&& ) = default;

    /**
     *  @brief Assignment operator
     *
     *  @param coefficient   the zero order coefficient
     */
    Derived& operator=( const Y& value ) {

      this->coefficients_ = { value };
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Constructor
     *
     *  There must be at least 1 coefficient. Trailing zeros in the coefficients are
     *  removed (if all are zero, a single zero coefficient will remain).
     *
     *  @param coefficients   the coefficients of the series (from lowest to highest
     *                        order coefficient)
     *  @param domain         the domain of the series
     */
    SeriesBase( DomainVariant domain, std::vector< Y > coefficients ) :
      Parent( std::move( domain ) ),
      coefficients_( std::move( coefficients ) ) {

      verifyCoefficients( this->coefficients() );
      this->trimCoefficients();
    }

  public:

    /* methods */

    /**
     *  @brief Return the series coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the series order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    /**
     *  @brief Calculate the real roots of the series so that f(x) = a
     *
     *  This function calculates all roots on the real axis of the series.
     *
     *  The roots of the series are the eigenvalues of the companion matrix whose
     *  elements are trivial functions of the coefficients of the series. The
     *  resulting roots are in the complex plane so the roots that are not on the
     *  real axis are filtered out.
     *
     *  @param[in] a   the value of a (default is zero)
     */
    std::vector< X > roots( const Y& a = Y( 0. ) ) const {

      std::vector< X > roots;
      roots.reserve( this->order() );

      if ( 1 == this->order() ) {

        roots.emplace_back( - ( this->coefficients()[0] - a ) / this->coefficients()[1] );
      }
      else if ( 1 < this->order() ) {

        Eigen::EigenSolver< Matrix< Y > >
        solver( static_cast< const Derived* >( this )->companionMatrix( a ), false );

        Derived derivative = this->derivative();
        auto functor = [&a, this] ( const X& x ) { return ( *this )( x ) - a; };

        for ( const auto& value : solver.eigenvalues() ) {

          if ( isCloseToZero( value.imag() ) ) {

            roots.emplace_back( !isCloseToZero( derivative( value.real() ) )
                                ? newton( value.real(), functor, derivative )
                                : value.real() );
          }
        }

        std::sort( roots.begin(), roots.end() );
        roots.erase( std::unique( roots.begin(), roots.end() ), roots.end() );
      }

      return roots;
    }

    /**
     *  @brief Return the derivative of the series
     */
    Derived derivative() const {

      const unsigned int order = this->order();
      if ( 0 == order ) {

        return Derived( SeriesBase( this->domain(), { Y( 0. ) } ) );
      }
      else {

        return static_cast< const Derived* >( this )->calculateDerivative();
      }
    }

    /**
     *  @brief Return the primitive (or antiderivative) of the series
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    Derived primitive( const X& left = X( 0. ) ) const {

      return static_cast< const Derived* >( this )->calculatePrimitive( left );
    }

    /**
     *  @brief Linearise the series and return a LinearLinearTable
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    InterpolationTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

      if ( ! std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

        Log::error( "Cannot linearise the series because it does not have an "
                    "interval domain" );
        throw std::exception();
      }

      const auto domain = std::get< IntervalDomain< X > >( this->domain() );

      if ( 0 == this->order() ) {

        return InterpolationTable< X, Y >( { domain.lowerLimit(), domain.upperLimit() },
                                           { this->coefficients().front(),
                                             this->coefficients().front() } );
      }
      else if ( 1 == this->order() ) {

        const auto a = this->coefficients().back();
        const auto b = this->coefficients().front();
        return InterpolationTable< X, Y >( { domain.lowerLimit(), domain.upperLimit() },
                                           { a * domain.lowerLimit() + b,
                                             a * domain.upperLimit() + b } );
      }
      else {

        std::vector< X > x;
        std::vector< Y > y;
        linearisation::Lineariser lineariser( x, y );
        lineariser( linearisation::grid( *this, domain.lowerLimit(), domain.upperLimit() ),
                    *this,
                    std::forward< Convergence >( convergence ),
                    linearisation::MidpointSplit< X >() );

        return InterpolationTable< X, Y >( std::move( x ), std::move( y ) );
      }
    }

    /**
     *  @brief Calculate the integral over the series domain
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I integral() const {

      return static_cast< const Derived* >( this )->calculateIntegral();
    }

    /**
     *  @brief Calculate the mean over the series domain
     *
     *  Note: unnormalised and normalised tables return the same mean value.
     */
    X mean() const {

      return static_cast< const Derived* >( this )->calculateMean() / this->integral();
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived& operator+=( const S& right ) noexcept {

      this->coefficients_[0] += right;
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived& operator-=( const S& right ) noexcept {

      return this->operator+=( -right );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived& operator*=( const S& right ) noexcept {

      for ( auto& value : this->coefficients_ ) {

        value *= right;
      }
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived& operator/=( const S& right ) noexcept {

      return this->operator*=( Y( 1. ) / right );
    }

    /**
     *  @brief Series and scalar addition
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived operator+( const S& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result += right;
      return result;
    }

    /**
     *  @brief Series and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived operator-( const S& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result -= right;
      return result;
    }

    /**
     *  @brief Series and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived operator*( const S& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result *= right;
      return result;
    }

    /**
     *  @brief Series and scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived operator/( const S& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    Derived operator-() const {

      Derived result = *static_cast< const Derived* >( this );
      result *= Y( -1. );
      return result;
    }

    /**
     *  @brief Inplace series addition
     *
     *  There is no domain checking on the two series. It is up to the user to
     *  verify that the domain of the two series are compatible.
     *
     *  @todo add domain check?
     *
     *  @param[in] right    the series
     */
    Derived& operator+=( const Derived& right ) noexcept {

      if ( this->coefficients().size() < right.coefficients().size() ) {

        this->coefficients_.resize( right.coefficients().size(), Y( 0. ) );
      }
      for ( unsigned int i = 0; i < right.coefficients().size(); ++i ) {

        this->coefficients_[i] += right.coefficients()[i];
      }
      this->trimCoefficients();
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace series subtraction
     *
     *  There is no domain checking on the two series. It is up to the user to
     *  verify that the domain of the two series are compatible.
     *
     *  @todo add domain check?
     *
     *  @param[in] right    the series
     */
    Derived& operator-=( const Derived& right ) noexcept {

      if ( this->coefficients().size() < right.coefficients().size() ) {

        this->coefficients_.resize( right.coefficients().size(), Y( 0. ) );
      }
      for ( unsigned int i = 0; i < right.coefficients().size(); ++i ) {

        this->coefficients_[i] -= right.coefficients()[i];
      }
      this->trimCoefficients();
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace series multiplication
     *
     *  There is no domain checking on the two series. It is up to the user to
     *  verify that the domain of the two series are compatible.
     *
     *  @todo add domain check?
     *
     *  @todo make noexcept when all derived series have an implementation
     *
     *  @param[in] right    the series
     */
    Derived& operator*=( const Derived& right ) {

      this->coefficients_ = static_cast< const Derived* >( this )->calculateProduct( right.coefficients() );
      this->trimCoefficients();
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Series and series addition
     *
     *  @param[in] right    the series
     */
    Derived operator+( const Derived& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result += right;
      return result;
    }

    /**
     *  @brief Series and series subtraction
     *
     *  @param[in] right    the series
     */
    Derived operator-( const Derived& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result -= right;
      return result;
    }

    /**
     *  @brief Series and series multiplication
     *
     *  @todo make noexcept when all derived series have an implementation
     *
     *  @param[in] right    the series
     */
    Derived operator*( const Derived& right ) const {

      Derived result = *static_cast< const Derived* >( this );
      result *= right;
      return result;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the series on the right hand side
     */
    bool operator==( const Derived& right ) const noexcept {

      return this->domain() == right.domain() &&
             this->coefficients() == right.coefficients();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the series on the right hand side
     */
    bool operator!=( const Derived& right ) const noexcept {

      return ! this->operator==( right );
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

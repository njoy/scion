#ifndef NJOY_SCION_MATH_SERIESBASE
#define NJOY_SCION_MATH_SERIESBASE

// system includes

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
    #include "scion/math/SeriesBase/src/verifyCoefficients.hpp"
    #include "scion/math/SeriesBase/src/trimCoefficients.hpp"

  protected:

    /* constructor */

    #include "scion/math/SeriesBase/src/ctor.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the Legendre coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the Legendre order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    #include "scion/math/SeriesBase/src/roots.hpp"
    #include "scion/math/SeriesBase/src/derivative.hpp"
    #include "scion/math/SeriesBase/src/primitive.hpp"
    #include "scion/math/SeriesBase/src/linearise.hpp"

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    Derived& operator+=( const Y& right ) noexcept {

      this->coefficients_[0] += right;
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    Derived& operator-=( const Y& right ) noexcept {

      return this->operator+=( -right );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    Derived& operator*=( const Y& right ) noexcept {

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
    Derived& operator/=( const Y& right ) noexcept {

      return this->operator*=( Y( 1. ) / right );
    }

    /**
     *  @brief Series and scalar addition
     *
     *  @param[in] right    the scalar
     */
    Derived operator+( const Y& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result += right;
      return result;
    }

    /**
     *  @brief Series and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    Derived operator-( const Y& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result -= right;
      return result;
    }

    /**
     *  @brief Series and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    Derived operator*( const Y& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result *= right;
      return result;
    }

    /**
     *  @brief Series and scalar division
     *
     *  @param[in] right    the scalar
     */
    Derived operator/( const Y& right ) const noexcept {

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

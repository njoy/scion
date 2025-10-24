#ifndef NJOY_SCION_MATH_SERIESRATIOBASE
#define NJOY_SCION_MATH_SERIESRATIOBASE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for ratios of series expansion objects
   *
   *  This base class provides the common interface for ratios of series
   *  expansions such as the polynomial series, Legendre series and
   *  Chebyshev series.
   *
   *  @todo see about adding a capability to simplify the ratio?
   */
  template < typename Derived, typename Series, typename X, typename Y >
  class SeriesRatioBase : public OneDimensionalFunctionBase< Derived, X, Y > {

    /* type aliases */
    using Parent = OneDimensionalFunctionBase< Derived, X, Y >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  private:

    /* fields */
    Series numerator_;
    Series denominator_;

  protected:

    /* constructor */

    #include "scion/math/SeriesRatioBase/src/ctor.hpp"

    /* auxiliary function */

    #include "scion/math/SeriesRatioBase/src/simplify.hpp"
    #include "scion/math/SeriesRatioBase/src/evaluate.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the series in the numerator of the ratio
     */
    const Series& numerator() const noexcept {

      return this->numerator_;
    }

    /**
     *  @brief Return the series in the denominator of the ratio
     */
    const Series& denominator() const noexcept {

      return this->denominator_;
    }

    /**
     *  @brief Return the derivative of the ratio
     */
    Derived derivative() const {

      if ( this->denominator().order() == 0 ) {

        Series numerator = this->numerator().derivative();
        Series denominator = this->denominator();
        return Derived( std::move( numerator ), std::move( denominator ) );
      }
      else {

        Series numerator = this->numerator().derivative() * this->denominator() -
                           this->numerator() * this->denominator().derivative();
        Series denominator = this->denominator() * this->denominator();
        return Derived( std::move( numerator ), std::move( denominator ) );
      }
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    Derived& operator+=( const S& right ) noexcept {

      if ( this->denominator().order() == 0 ) {

        this->numerator_ += right;
      }
      else {

        this->numerator_ += right * this->denominator_;
      }
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

      this->numerator_ *= right;
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
    Derived& operator+=( const Series& right ) noexcept {

      if ( this->denominator().order() == 0 ) {

        this->numerator_ += right;
      }
      else {

        this->numerator_ += this->denominator_ * right;
      }
      return *static_cast< Derived* >( this );
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

      bool has_denominator = right.denominator().order() != 0;

      if ( has_denominator ) {

        this->numerator_ *= right.denominator();
      }
      if ( this->denominator().order() == 0 ) {

        this->numerator_ += right.numerator();
      }
      else {

        this->numerator_ += this->denominator() * right.numerator();
      }
      if ( has_denominator ) {

        this->denominator_ *= right.denominator();
      }
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
    Derived& operator-=( const Series& right ) noexcept {

      if ( this->denominator().order() == 0 ) {

        this->numerator_ -= right;
      }
      else {

        this->numerator_ -= this->denominator_ * right;
      }
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

      bool has_denominator = right.denominator().order() != 0;

      if ( has_denominator ) {

        this->numerator_ *= right.denominator();
      }
      if ( this->denominator().order() == 0 ) {

        this->numerator_ -= right.numerator();
      }
      else {

        this->numerator_ -= this->denominator() * right.numerator();
      }
      if ( has_denominator ) {

        this->denominator_ *= right.denominator();
      }
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
    Derived& operator*=( const Series& right ) {

      this->numerator_ *= right;
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

      this->numerator_ *= right.numerator();
      if ( right.denominator().order() != 0 ) {

        this->denominator_ *= right.denominator();
      }
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace series division
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
    Derived& operator/=( const Series& right ) {

      this->denominator_ *= right;
      this->simplify();
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace series division
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
    Derived& operator/=( const Derived& right ) {

      this->numerator_ *= right.denominator();
      this->denominator_ *= right.numerator();
      this->simplify();
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Series and series addition
     *
     *  @param[in] right    the series
     */
    Derived operator+( const Series& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result += right;
      return result;
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
    Derived operator-( const Series& right ) const noexcept {

      Derived result = *static_cast< const Derived* >( this );
      result -= right;
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
    Derived operator*( const Series& right ) const {

      Derived result = *static_cast< const Derived* >( this );
      result *= right;
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
     *  @brief Series and series division
     *
     *  @todo make noexcept when all derived series have an implementation
     *
     *  @param[in] right    the series
     */
    Derived operator/( const Series& right ) const {

      Derived result = *static_cast< const Derived* >( this );
      result /= right;
      return result;
    }

    /**
     *  @brief Series and series division
     *
     *  @todo make noexcept when all derived series have an implementation
     *
     *  @param[in] right    the series
     */
    Derived operator/( const Derived& right ) const {

      Derived result = *static_cast< const Derived* >( this );
      result /= right;
      return result;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the series on the right hand side
     */
    bool operator==( const Derived& right ) const noexcept {

      return this->domain() == right.domain() &&
             this->numerator() == right.numerator() &&
             this->denominator() == right.denominator();
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

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
    #include "scion/math/ChebyshevApproximation/src/calculateCoefficients.hpp"
    #include "scion/math/ChebyshevApproximation/src/transform.hpp"

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    #include "scion/math/ChebyshevApproximation/src/ctor.hpp"

    /* interface implementation function */

    #include "scion/math/ChebyshevApproximation/src/evaluate.hpp"

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

    #include "scion/math/ChebyshevApproximation/src/derivative.hpp"
    #include "scion/math/ChebyshevApproximation/src/primitive.hpp"
    #include "scion/math/ChebyshevApproximation/src/roots.hpp"
    #include "scion/math/ChebyshevApproximation/src/linearise.hpp"

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation& operator+=( const Y& right ) {

      this->series_ += right;
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation& operator-=( const Y& right ) {

      return this->operator+=( -right );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation& operator*=( const Y& right ) {

      this->series_ *= right;
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation& operator/=( const Y& right ) {

      return this->operator*=( Y( 1. ) / right );
    }

    /**
     *  @brief Approximation and scalar addition
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation operator+( const Y& right ) const {

      ChebyshevApproximation result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief Approximation and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation operator-( const Y& right ) const {

      ChebyshevApproximation result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief Approximation and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation operator*( const Y& right ) const {

      ChebyshevApproximation result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief Approximation and scalar division
     *
     *  @param[in] right    the scalar
     */
    ChebyshevApproximation operator/( const Y& right ) const {

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
  template < typename X, typename Y = X >
  ChebyshevApproximation< X, Y >
  operator+( const Y& left, const ChebyshevApproximation< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and approximation subtraction
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the approximation
   */
  template < typename X, typename Y = X >
  ChebyshevApproximation< X, Y >
  operator-( const Y& left, const ChebyshevApproximation< X, Y >& right ) {

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
  template < typename X, typename Y = X >
  ChebyshevApproximation< X, Y >
  operator*( const Y& left, const ChebyshevApproximation< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

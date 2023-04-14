#ifndef NJOY_SCION_MATH_POLYNOMIALSERIES
#define NJOY_SCION_MATH_POLYNOMIALSERIES

// system includes
#include <vector>

// other includes
#include "scion/math/horner.hpp"
#include "scion/math/FunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A polynomial function y -> f(x) = sum c_i x^i of order n
   *
   *  This class represents a polynomial function y -> f(x) = sum c_i x^i of
   *  order n (i between 0 and n) defined over a domain. Currently, the domain
   *  can either be the open domain where every value of x is allowed or the
   *  interval domain that restricts x to an interval [a,b].
   *
   *  The horner scheme is used for the evaluation of the series.
   */
  template < typename X, typename Y = X >
  class PolynomialSeries : public FunctionBase< PolynomialSeries< X, Y >, X, Y > {

    using Parent = FunctionBase< PolynomialSeries< X, Y >, X, Y >;

    /* fields */
    std::vector< Y > coefficients_;

    /* auxiliary function */
    #include "scion/math/PolynomialSeries/src/verifyCoefficients.hpp"

  public:

    /* type aliases */
    using DomainVariant = typename Parent::DomainVariant;

    /* constructor */
    #include "scion/math/PolynomialSeries/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the Legendre coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the polynomial order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    #include "scion/math/PolynomialSeries/src/evaluate.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

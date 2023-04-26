#ifndef NJOY_SCION_MATH_POLYNOMIALSERIES
#define NJOY_SCION_MATH_POLYNOMIALSERIES

// system includes
#include <complex>
#include <vector>

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/compare.hpp"
#include "scion/math/horner.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/newton.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/math/LinearLinearTable.hpp"

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
   *  restricts x to an interval [a,b]. An exception is thrown for values
   *  outside of the domain.
   *
   *  The horner scheme is used for the evaluation of the series.
   */
  template < typename X, typename Y = X >
  class PolynomialSeries : public FunctionBase< PolynomialSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< PolynomialSeries< X, Y >, X, Y >;

    /* fields */
    std::vector< Y > coefficients_;

    /* auxiliary function */
    #include "scion/math/PolynomialSeries/src/verifyCoefficients.hpp"
    #include "scion/math/PolynomialSeries/src/companionMatrix.hpp"
    #include "scion/math/PolynomialSeries/src/grid.hpp"

  public:

    /* type aliases */
    using DomainVariant = typename Parent::DomainVariant;

    /* constructor */
    #include "scion/math/PolynomialSeries/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the polynomial coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the polynomial series order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    #include "scion/math/PolynomialSeries/src/evaluate.hpp"
    #include "scion/math/PolynomialSeries/src/derivative.hpp"
    #include "scion/math/PolynomialSeries/src/roots.hpp"
    #include "scion/math/PolynomialSeries/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

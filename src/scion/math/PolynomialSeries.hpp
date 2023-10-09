#ifndef NJOY_SCION_MATH_POLYNOMIALSERIES
#define NJOY_SCION_MATH_POLYNOMIALSERIES

// system includes
#include <vector>

// other includes
#include "scion/math/horner.hpp"
#include "scion/math/matrix.hpp"
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
  template < typename X, typename Y = X >
  class PolynomialSeries : public SeriesBase< PolynomialSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = SeriesBase< PolynomialSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary function */

  public:

    /* type aliases */
    using DomainVariant = typename Parent::DomainVariant;

    /* constructor */
    #include "scion/math/PolynomialSeries/src/ctor.hpp"

    /* interface implementation function */

    #include "scion/math/PolynomialSeries/src/evaluate.hpp"
    #include "scion/math/PolynomialSeries/src/calculateDerivative.hpp"
    #include "scion/math/PolynomialSeries/src/calculatePrimitive.hpp"
    #include "scion/math/PolynomialSeries/src/companionMatrix.hpp"

    /* methods */

    using Parent::coefficients;
    using Parent::order;
    using Parent::roots;
    using Parent::derivative;
    using Parent::primitive;
    using Parent::linearise;
    using Parent::operator+;
    using Parent::operator-;
    using Parent::operator*;
    using Parent::operator/;
    using Parent::operator+=;
    using Parent::operator-=;
    using Parent::operator*=;
    using Parent::operator/=;
    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

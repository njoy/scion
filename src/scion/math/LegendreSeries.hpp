#ifndef NJOY_SCION_MATH_LEGENDRESERIES
#define NJOY_SCION_MATH_LEGENDRESERIES

// system includes
#include <vector>

// other includes
#include "scion/math/clenshaw.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/SeriesBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A Legendre series function y -> f(x) = sum c_i P_i(x) of order n
   *
   *  This class represents a Legendre series function y -> f(x) =
   *  sum c_i P_i(x) defined over the domain [-1,1].
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series
   *  using the following recursion relation for Legendre polynomials:
   *    P_(n+1) = (2n+1)/(n+1) x P_n - n/(n+1) P_(n-1)
   *
   *  The derivative function of a Legendre series function is another
   *  Legendre series function. The coefficients of the new Legendre series
   *  are calculated using the derivative of a Legendre polynomial as a
   *  function of other Legendre polynomials:
   *    d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...
   *  knowing that:
   *    d/dx P_0 = 0.0
   *    d/dx P_1 = P_0
   *
   *  This formula can be derived using the following property of Legendre
   *  polynomials:
   *    ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)
   *
   *  The primitive or antiderivative of a Legendre series function is another
   *  Legendre series function. The coefficients of the new Legendre series
   *  are calculated using the integral of a Legendre polynomial as a
   *  function of other Legendre polynomials:
   *    int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
   *
   *  The integrated series is defined so that the integral function for x = left
   *  equals 0.
   *
   *  The derivative and primitive function is defined over the same domain as
   *  the original function.
   */
  template < typename X, typename Y = X >
  class LegendreSeries : public SeriesBase< LegendreSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = SeriesBase< LegendreSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LegendreSeries/src/ctor.hpp"

    /* interface implementation function */

    #include "scion/math/LegendreSeries/src/evaluate.hpp"
    #include "scion/math/LegendreSeries/src/calculateDerivative.hpp"
    #include "scion/math/LegendreSeries/src/calculatePrimitive.hpp"
    #include "scion/math/LegendreSeries/src/companionMatrix.hpp"

    /* methods */

    using Parent::coefficients;
    using Parent::order;
    using Parent::roots;
    using Parent::derivative;
    using Parent::primitive;
    using Parent::linearise;
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

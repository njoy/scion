#ifndef NJOY_SCION_MATH_CHEBYSHEVSERIES
#define NJOY_SCION_MATH_CHEBYSHEVSERIES

// system includes
#include <vector>

// other includes
#include "scion/math/clenshaw.hpp"
#include "scion/math/compare.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/SeriesBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A Chebyshev series function y -> f(x) = sum c_i T_i(x) of order n
   *
   *  This class represents a Chebyshev series function y -> f(x) =
   *  sum c_i T_i(x) defined over the domain [-1,1].
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series
   *  using the following recursion relation for Chebyshev polynomials:
   *
   *    T_(n+1) = 2 x T_n - T_(n-1)
   *
   *  The derivative function of a Chebyshev series function is another
   *  Chebyshev series function. The coefficients of the new Chebyshev series
   *  are calculated using the derivative of a Chebyshev polynomial as a
   *  function of other Chebyshev polynomials:
   *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even
   *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd
   *
   *  This relation can be proven by mathematical induction.
   *
   *  The derivative function is defined over the same domain as the
   *  original function.
   */
  template < typename X, typename Y = X >
  class ChebyshevSeries : public SeriesBase< ChebyshevSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = SeriesBase< ChebyshevSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary function */
    #include "scion/math/ChebyshevSeries/src/companionMatrix.hpp"

  public:

    /* constructor */
    #include "scion/math/ChebyshevSeries/src/ctor.hpp"

    /* interface implementation function */

    #include "scion/math/ChebyshevSeries/src/evaluate.hpp"
    #include "scion/math/ChebyshevSeries/src/calculateDerivative.hpp"

    /* methods */

    #include "scion/math/ChebyshevSeries/src/primitive.hpp"
    #include "scion/math/ChebyshevSeries/src/roots.hpp"

    using Parent::coefficients;
    using Parent::order;
    using Parent::derivative;
    using Parent::linearise;
    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

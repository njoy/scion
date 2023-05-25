#ifndef NJOY_SCION_MATH_LEGENDRESERIES
#define NJOY_SCION_MATH_LEGENDRESERIES

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
   *  @brief A Legendre series function y -> f(x) = sum c_i P_i(x) of order n
   *
   *  This class represents a Legendre series function y -> f(x) =
   *  sum c_i P_i(x) defined over the domain [-1,1].
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series
   *  using the following recursion relation for Legendre polynomials:
   *
   *    P_(n+1) = (2n+1)/(n+1) x P_n - n/(n+1) P_(n-1)
   */
  template < typename X, typename Y = X >
  class LegendreSeries : public SeriesBase< LegendreSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = SeriesBase< LegendreSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary function */
    #include "scion/math/LegendreSeries/src/companionMatrix.hpp"

  public:

    /* constructor */
    #include "scion/math/LegendreSeries/src/ctor.hpp"

    /* interface implementation function */

    #include "scion/math/LegendreSeries/src/evaluate.hpp"
    #include "scion/math/LegendreSeries/src/calculateDerivative.hpp"

    /* methods */

    #include "scion/math/LegendreSeries/src/primitive.hpp"
    #include "scion/math/LegendreSeries/src/roots.hpp"

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

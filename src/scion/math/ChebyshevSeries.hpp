#ifndef NJOY_SCION_MATH_CHEBYSHEVSERIES
#define NJOY_SCION_MATH_CHEBYSHEVSERIES

// system includes
#include <vector>

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/clenshaw.hpp"
#include "scion/math/compare.hpp"
#include "scion/math/matrix.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/math/LinearLinearTable.hpp"

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
   */
  template < typename X, typename Y = X >
  class ChebyshevSeries : public FunctionBase< ChebyshevSeries< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< ChebyshevSeries< X, Y >, X, Y >;

    /* fields */
    std::vector< Y > coefficients_;

    /* auxiliary function */
    #include "scion/math/ChebyshevSeries/src/verifyCoefficients.hpp"
    #include "scion/math/ChebyshevSeries/src/companionMatrix.hpp"

  public:

    /* constructor */
    #include "scion/math/ChebyshevSeries/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the Chebyshev coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the Chebyshev order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    #include "scion/math/ChebyshevSeries/src/evaluate.hpp"
    #include "scion/math/ChebyshevSeries/src/derivative.hpp"
    #include "scion/math/ChebyshevSeries/src/primitive.hpp"
    #include "scion/math/ChebyshevSeries/src/roots.hpp"
    #include "scion/math/ChebyshevSeries/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

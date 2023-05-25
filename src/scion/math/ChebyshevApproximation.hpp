#ifndef NJOY_SCION_MATH_CHEBYSHEVAPPROXIMATION
#define NJOY_SCION_MATH_CHEBYSHEVAPPROXIMATION

// system includes
#include <vector>

// other includes
#include "scion/math/FunctionBase.hpp"
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
   *  a domain transformation is required to go from one to the other.
   */
  template < typename X, typename Y = X >
  class ChebyshevApproximation : public FunctionBase< ChebyshevApproximation< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< ChebyshevApproximation< X, Y >, X, Y >;

    /* fields */
    X lower_;
    X upper_;
    ChebyshevSeries< X, Y > series_;

    /* auxiliary function */
    #include "scion/math/ChebyshevApproximation/src/calculateCoefficients.hpp"
    #include "scion/math/ChebyshevApproximation/src/transform.hpp"

  public:

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

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

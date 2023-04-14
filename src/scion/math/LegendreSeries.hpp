#ifndef NJOY_SCION_MATH_LEGENDRESERIES
#define NJOY_SCION_MATH_LEGENDRESERIES

// system includes
#include <vector>

// other includes
#include "scion/math/clenshaw.hpp"
#include "scion/math/FunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A Legendre series function y -> f(x) = sum c_i P_i(x) of order n
   *
   *  This class represents a Legendre series function y -> f(x) =
   *  sum c_i P_i(x) defined over the domain [-1,1]. An exception is thrown
   *  for values outside of the domain.
   *
   *  The Clenshaw recursion scheme is used for the evaluation of the series.
   */
  template < typename X, typename Y = X >
  class LegendreSeries : public FunctionBase< LegendreSeries< X, Y >, X, Y > {

    using Parent = FunctionBase< LegendreSeries< X, Y >, X, Y >;

    /* fields */
    std::vector< Y > coefficients_;

    /* auxiliary function */
    #include "scion/math/LegendreSeries/src/verifyCoefficients.hpp"

  public:

    /* constructor */
    #include "scion/math/LegendreSeries/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the Legendre coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the Legendre order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    #include "scion/math/LegendreSeries/src/evaluate.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

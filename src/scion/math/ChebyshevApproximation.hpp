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

    /**
     *  @brief Transform x in [a, b] to xprime in [-1, 1]
     *
     *  @param[in] x    the value of x to transform into xprime
     */
    X transform( const X& x ) const {

      return ( 2. * x - ( this->upper_ + this->lower_ ) )
             / ( this->upper_ - this->lower_ );
    }

    /**
     *  @brief Transform xprime in [-1, 1] to x in [a, b]
     *
     *  @param[in] xprime    the value of xprime to transform into x
     */
    X invert( const X& xprime ) const {

      return ( xprime + X( 1 ) ) * ( this->upper_ - this->lower_ ) / X( 2 ) + this->lower_;
    }

  public:

    /* constructor */
    #include "scion/math/ChebyshevApproximation/src/ctor.hpp"

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

    #include "scion/math/ChebyshevApproximation/src/evaluate.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

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
   *  @brief A Legendre series function y -> f(x) = sum c_i P_i(x)
   *
   *  This class represents a Legendre series function y -> f(x) =
   *  sum c_i P_i(x) defined over the domain [-1,1]. An exception is thrown
   *  for values outside of the domain.
   */
  template < typename X, typename Y = X >
  class LegendreSeries : public FunctionBase< LegendreSeries< X, Y >, X, Y > {

    friend class FunctionBase< LegendreSeries< X, Y >, X, Y >;
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

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      if ( ! this->isInside( x ) ) {

        Log::error( "Legendre polynomials are defined for x values in the [-1,1] interval" );
        Log::info( "The value of x requested: {}", x );
        throw std::exception();
      }

      auto a = [] ( unsigned int k, const X& x ) -> Y {

        return static_cast< Y >( 2 * k + 1 ) / static_cast< Y >( k + 1 ) * x;
      };
      auto b = [] ( unsigned int k, const X& x ) -> Y {

        return - static_cast< Y >( k ) / static_cast< Y >( k + 1 );
      };

      return math::clenshaw( this->coefficients().rbegin(),
                             this->coefficients().rend(),
                             a, b, 1., x, x );
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

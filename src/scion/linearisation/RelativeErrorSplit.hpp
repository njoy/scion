#ifndef NJOY_SCION_LINEARISATION_RELATIVEERRORSPLIT
#define NJOY_SCION_LINEARISATION_RELATIVEERRORSPLIT

// system includes

// other includes
#include "scion/linearisation/SplitBase.hpp"
#include "scion/math/newton.hpp"

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief A split functor that uses the relative error between the
   *         function and the linear approximation over the panel
   *
   *  The relative difference between the function and the linear approximation
   *  over the panel is the largest where d/dx ( ( f(x) - a x - b ) / f(x) ) = 0.
   *
   *  Note: this split function should only be used on panels where f(x) has
   *  a second derivative different from zero to avoid divergence in the
   *  newton method.
   */
  template< typename X, typename Function, typename FirstDerivative,
            typename SecondDerivative, typename Y = X >
  class RelativeErrorSplit :
      public SplitBase< RelativeErrorSplit< X, Function, FirstDerivative,
                                            SecondDerivative, Y >, X, Y > {

    /* friend declarations */
    friend class SplitBase< RelativeErrorSplit< X, Function, FirstDerivative,
                                                 SecondDerivative, Y >, X, Y >;

    /* type aliases */
    using Parent = SplitBase< RelativeErrorSplit< X, Function, FirstDerivative,
                                                   SecondDerivative, Y >, X, Y >;

    /* fields */
    Function function_;
    FirstDerivative first_;
    SecondDerivative second_;
    int iterations_;

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Split the panel at the point of maximum relative error
     *
     *  @param[in] xLeft        the left value on the x interval
     *  @param[in] xRight       the right value on the x interval
     *  @param[in] yLeft        the left value on the y interval
     *  @param[in] yRight       the right value on the y interval
     */
    X split( const X& xLeft, const X& xRight,
             const Y& yLeft, const Y& yRight ) const {

      const X midpoint = 0.5 * ( xLeft + xRight );
      const Y slope = ( yRight - yLeft ) / ( xRight - xLeft );
      const Y intercept = yLeft - slope * xLeft;

      const auto& function = [&] ( const X& x ) {

        return slope * this->function()( x ) - ( slope * x + intercept ) * this->firstDerivative()( x );
      };
      auto derivative = [&] ( const X& x ) {

        return -( slope * x + intercept ) * this->secondDerivative()( x );
      };

      const X root = math::newton( midpoint, function,derivative, this->iterations() );
      return ( root > xLeft && root < xRight ) ? root : midpoint;
    }

  public:

    /* constructor */
    #include "scion/linearisation/RelativeErrorSplit/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the function
     */
    const Function& function() const {

      return this->function_;
    }

    /**
     *  @brief Return the first derivative of the function
     */
    const FirstDerivative& firstDerivative() const {

      return this->first_;
    }

    /**
     *  @brief Return the second derivative of the function
     */
    const SecondDerivative& secondDerivative() const {

      return this->second_;
    }

    /**
     *  @brief Return the number of iterations
     */
    int iterations() const {

      return this->iterations_;
    }

    using Parent::operator();
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

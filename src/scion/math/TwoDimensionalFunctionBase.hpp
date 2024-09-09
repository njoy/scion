#ifndef NJOY_SCION_MATH_TWODIMENSIONALFUNCTIONBASE
#define NJOY_SCION_MATH_TWODIMENSIONALFUNCTIONBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for two dimensional function objects modelling y = f(x,y)
   *
   *  This base class provides the common interface for all two dimensional
   *  function objects. This includes function evaluation.
   */
  template < typename Derived, typename X, typename Y, typename Z >
  class TwoDimensionalFunctionBase {

  public:

    /* type aliases */

    using XType = X;
    using YType = Y;
    using ZType = Z;

    /* methods */

    /**
     *  @brief Evaluate the function for a value of x and y
     *
     *  @param x   the value to be evaluated
     */
    Z operator()( const X& x, const Y& y ) const {

      return static_cast< const Derived* >( this )->evaluate( x, y );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_MATH_ONEDIMENSIONALFUNCTIONBASE
#define NJOY_SCION_MATH_ONEDIMENSIONALFUNCTIONBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for one dimensional function objects modelling y = f(x)
   *
   *  This base class provides the common interface for all one dimensional
   *  function objects. This includes domain testing and function evaluation.
   *
   *  Any class deriving from this base class must implement a lower(), upper()
   *  and evaluate() function.
   */
  template < typename Derived, typename X, typename Y >
  class OneDimensionalFunctionBase {

    /* fields */

    /* auxiliary function */

  protected:

    /* constructor */

    OneDimensionalFunctionBase() = default;

    OneDimensionalFunctionBase( const OneDimensionalFunctionBase& ) = default;
    OneDimensionalFunctionBase( OneDimensionalFunctionBase&& ) = default;

    OneDimensionalFunctionBase& operator=( const OneDimensionalFunctionBase& ) = default;
    OneDimensionalFunctionBase& operator=( OneDimensionalFunctionBase&& ) = default;

  public:

    /* type aliases */

    using XType = X;
    using YType = Y;

    /* methods */

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y operator()( const X& x ) const {

      return static_cast< const Derived* >( this )->evaluate( x );
    }

    /**
     *  @brief Return the lower limit of the domain
     */
    decltype(auto) lowerLimit() const noexcept {

      return static_cast< const Derived* >( this )->lower();
    }

    /**
     *  @brief Return the upper limit of the domain
     */
    decltype(auto) upperLimit() const noexcept {

      return static_cast< const Derived* >( this )->upper();
    }

    /**
     *  @brief Check whether or not a value is inside the domain (including
     *         boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isInside( const X& x ) const noexcept {

      return ( this->lowerLimit() <= x ) && ( x <= this->upperLimit() );
    }

    /**
     *  @brief Check whether or not a value is contained within the domain
     *         (excluding boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isContained( const X& x ) const noexcept {

      return ( this->lowerLimit() < x ) && ( x < this->upperLimit() );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

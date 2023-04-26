#ifndef NJOY_SCION_LINEARISATION_CONVERGENCEBASE
#define NJOY_SCION_LINEARISATION_CONVERGENCEBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief Base class for the linearisation convergence functor
   *
   *  For the convergence of the Lineariser, the following signature function
   *  is used:
   *
   *    bool operator()( trial, reference, xLeft, xRight, yLeft, yRight )
   */
  template< typename Derived, typename X, typename Y = X >
  class ConvergenceBase  {

  protected:

    /* constructor */
    ConvergenceBase() = default;

  public:

    /**
     *  @brief Test convergence
     *
     *  @param x   the value to be evaluated
     */
    Y operator()( const Y& trial, const Y& reference,
                  const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->evaluate( trial, reference,
                                                              xLeft, xRight,
                                                              yLeft, yRight );
    }
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_LINEARISATION_SPLITBASE
#define NJOY_SCION_LINEARISATION_SPLITBASE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief Base class for splitting the panel during linearisation
   *
   *  For splitting the panel in the Lineariser, the following signature function
   *  is used:
   *
   *    bool operator()( xLeft, xRight, yLeft, yRight )
   */
  template< typename Derived, typename X, typename Y = X >
  class SplitBase  {

  protected:

    /* constructor */
    SplitBase() = default;

  public:

    /**
     *  @brief Split the panel
     *
     *  @param[in] xLeft        the left value on the x interval
     *  @param[in] xRight       the right value on the x interval
     *  @param[in] yLeft        the left value on the y interval
     *  @param[in] yRight       the right value on the y interval
     */
    Y operator()( const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) const {

      return static_cast< const Derived* >( this )->split( xLeft, xRight,
                                                           yLeft, yRight );
    }
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

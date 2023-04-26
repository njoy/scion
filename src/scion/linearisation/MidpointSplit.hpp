#ifndef NJOY_SCION_LINEARISATION_MIDPOINTSPLIT
#define NJOY_SCION_LINEARISATION_MIDPOINTSPLIT

// system includes

// other includes
#include "scion/linearisation/SplitBase.hpp"

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief A split functor using a panel's midpoint
   */
  template< typename X, typename Y = X >
  class MidpointSplit : public SplitBase< MidpointSplit< X, Y >, X, Y > {

    /* type aliases */
    using Parent = SplitBase< MidpointSplit< X, Y >, X, Y >;

  public:

    /* constructor */
    MidpointSplit() = default;

    /* methods */

    /**
     *  @brief Split the panel by returning the midpoint of the panel
     *
     *  @param[in] xLeft        the left value on the x interval
     *  @param[in] xRight       the right value on the x interval
     */
    X evaluate( const X& xLeft, const X& xRight ) const {

      return X( 0.5 ) * ( xLeft + xRight );
    }

    using Parent::operator();
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

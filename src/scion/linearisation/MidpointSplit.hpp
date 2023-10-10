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

    /* friend declarations */
    friend class SplitBase< MidpointSplit< X, Y >, X, Y >;

    /* type aliases */
    using Parent = SplitBase< MidpointSplit< X, Y >, X, Y >;

    /* interface implementation functions */

    /**
     *  @brief Split the panel by returning the midpoint of the panel
     *
     *  @param[in] xLeft        the left value on the x interval
     *  @param[in] xRight       the right value on the x interval
     *  @param[in] yLeft        the left value on the y interval
     *  @param[in] yRight       the right value on the y interval
     */
    X split( const X& xLeft, const X& xRight,
             const Y&,       const Y& ) const {

      return 0.5 * ( xLeft + xRight );
    }

  public:

    /* constructor */
    MidpointSplit() = default;

    /* methods */

    using Parent::operator();
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

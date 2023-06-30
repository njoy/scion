#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_2
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_2

// system includes
#include <array>

// other includes
#include "scion/integration/quadrature.hpp"
#include "scion/integration/GaussQuadratureBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief The Gauss-Lobatto 2-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLobatto< 2, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 2, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 2, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 2; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 2 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 2 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 1.000000000000000e+0 },
        std::pair< X, double >{  1.000000000000000e+0, 1.000000000000000e+0 } };
      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

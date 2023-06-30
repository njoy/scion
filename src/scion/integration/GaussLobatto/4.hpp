#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_4
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_4

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
   *  @brief The Gauss-Lobatto 4-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLobatto< 4, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 4, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 4, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 4; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 4 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 4 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 1.666666666666667e-1 },
        std::pair< X, double >{ -4.472135954999579e-1, 8.333333333333334e-1 },
        std::pair< X, double >{  4.472135954999579e-1, 8.333333333333334e-1 },
        std::pair< X, double >{  1.000000000000000e+0, 1.666666666666667e-1 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

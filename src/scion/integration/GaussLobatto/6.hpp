#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_6
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_6

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
   *  @brief The Gauss-Lobatto 6-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLobatto< 6, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 6, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 6, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 6; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 6 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 6 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 6.666666666666668e-2 },
        std::pair< X, double >{ -7.650553239294646e-1, 3.784749562978472e-1 },
        std::pair< X, double >{ -2.852315164806451e-1, 5.548583770354861e-1 },
        std::pair< X, double >{  2.852315164806451e-1, 5.548583770354861e-1 },
        std::pair< X, double >{  7.650553239294646e-1, 3.784749562978472e-1 },
        std::pair< X, double >{  1.000000000000000e+0, 6.666666666666668e-2 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

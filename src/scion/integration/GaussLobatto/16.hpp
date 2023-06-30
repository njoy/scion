#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_16
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_16

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
   *  @brief The Gauss-Lobatto 16-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 29 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLobatto< 16, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 16, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 16, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 16; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 16 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 16 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 8.333333333333333e-3 },
        std::pair< X, double >{ -9.695680462702180e-1, 5.085036100591971e-2 },
        std::pair< X, double >{ -8.992005330934721e-1, 8.939369732593086e-2 },
        std::pair< X, double >{ -7.920082918618150e-1, 1.242553821325142e-1 },
        std::pair< X, double >{ -6.523887028824931e-1, 1.540269808071644e-1 },
        std::pair< X, double >{ -4.860594218871376e-1, 1.774919133917042e-1 },
        std::pair< X, double >{ -2.998304689007632e-1, 1.936900238252035e-1 },
        std::pair< X, double >{ -1.013262735219495e-1, 2.019583081782299e-1 },
        std::pair< X, double >{  1.013262735219495e-1, 2.019583081782299e-1 },
        std::pair< X, double >{  2.998304689007632e-1, 1.936900238252035e-1 },
        std::pair< X, double >{  4.860594218871376e-1, 1.774919133917042e-1 },
        std::pair< X, double >{  6.523887028824931e-1, 1.540269808071644e-1 },
        std::pair< X, double >{  7.920082918618151e-1, 1.242553821325142e-1 },
        std::pair< X, double >{  8.992005330934721e-1, 8.939369732593086e-2 },
        std::pair< X, double >{  9.695680462702180e-1, 5.085036100591971e-2 },
        std::pair< X, double >{  1.000000000000000e+0, 8.333333333333333e-3 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

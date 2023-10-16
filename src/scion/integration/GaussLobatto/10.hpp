#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_10
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_10

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
   *  @brief The Gauss-Lobatto 10-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 17 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLobatto< 10, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 10, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 10, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 10; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 10 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 10 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 2.222222222222222e-2 },
        std::pair< X, double >{ -9.195339081664589e-1, 1.333059908510699e-1 },
        std::pair< X, double >{ -7.387738651055051e-1, 2.248893420631266e-1 },
        std::pair< X, double >{ -4.779249498104445e-1, 2.920426836796838e-1 },
        std::pair< X, double >{ -1.652789576663870e-1, 3.275397611838975e-1 },
        std::pair< X, double >{  1.652789576663870e-1, 3.275397611838975e-1 },
        std::pair< X, double >{  4.779249498104445e-1, 2.920426836796838e-1 },
        std::pair< X, double >{  7.387738651055051e-1, 2.248893420631266e-1 },
        std::pair< X, double >{  9.195339081664589e-1, 1.333059908510699e-1 },
        std::pair< X, double >{  1.000000000000000e+0, 2.222222222222222e-2 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_10
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_10

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
   *  @brief The Gauss-Legendre 10-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 19 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 10, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 10, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 10, X, Y >, X, Y >;

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

        std::pair< X, double >{ -0.9739065285171717, 0.0666713443086881 },
        std::pair< X, double >{ -0.8650633666889845, 0.1494513491505804 },
        std::pair< X, double >{ -0.6794095682990244, 0.2190863625159820 },
        std::pair< X, double >{ -0.4333953941292472, 0.2692667193099965 },
        std::pair< X, double >{ -0.1488743389816312, 0.2955242247147530 },
        std::pair< X, double >{  0.1488743389816312, 0.2955242247147530 },
        std::pair< X, double >{  0.4333953941292472, 0.2692667193099965 },
        std::pair< X, double >{  0.6794095682990244, 0.2190863625159820 },
        std::pair< X, double >{  0.8650633666889845, 0.1494513491505804 },
        std::pair< X, double >{  0.9739065285171717, 0.0666713443086881 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

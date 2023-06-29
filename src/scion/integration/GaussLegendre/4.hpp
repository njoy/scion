#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_4
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_4

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
   *  @brief The Gauss-Legendre 4-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 7 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 4, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 4, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 4, X, Y >, X, Y >;

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

        std::pair< X, double >{ -0.8611363115940526, 0.3478548451374537 },
        std::pair< X, double >{ -0.3399810435848563, 0.6521451548625462 },
        std::pair< X, double >{  0.3399810435848563, 0.6521451548625462 },
        std::pair< X, double >{  0.8611363115940526, 0.3478548451374537 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

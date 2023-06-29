#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_6
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_6

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
   *  @brief The Gauss-Legendre 6-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 7 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 6, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 6, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 6, X, Y >, X, Y >;

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

        std::pair< X, double >{ -0.9324695142031520, 0.1713244923791698 },
        std::pair< X, double >{ -0.6612093864662645, 0.3607615730481389 },
        std::pair< X, double >{ -0.2386191860831969, 0.4679139345726914 },
        std::pair< X, double >{  0.2386191860831969, 0.4679139345726914 },
        std::pair< X, double >{  0.6612093864662645, 0.3607615730481389 },
        std::pair< X, double >{  0.9324695142031520, 0.1713244923791698 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

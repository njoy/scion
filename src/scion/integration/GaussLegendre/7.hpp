#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_7
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_7

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
   *  @brief The Gauss-Legendre 7-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 13 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 7, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 7, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 7, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 7; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 7 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 7 > pairs = {

        std::pair< X, double >{ -9.49107912342758486e-1, 1.29484966168870647e-1 },
        std::pair< X, double >{ -7.41531185599394460e-1, 2.79705391489276589e-1 },
        std::pair< X, double >{ -4.05845151377397184e-1, 3.81830050505118312e-1 },
        std::pair< X, double >{  0.00000000000000000e+0, 4.17959183673468959e-1 },
        std::pair< X, double >{  4.05845151377397184e-1, 3.81830050505118312e-1 },
        std::pair< X, double >{  7.41531185599394460e-1, 2.79705391489276589e-1 },
        std::pair< X, double >{  9.49107912342758486e-1, 1.29484966168870647e-1 } };
      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_8
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_8

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
   *  @brief The Gauss-Legendre 8-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 7 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 8, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 8, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 8, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 8; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 8 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 8 > pairs = {

        std::pair< X, double >{ -9.60289856497536176e-1, 1.01228536290376689e-1 },
        std::pair< X, double >{ -7.96666477413626728e-1, 2.22381034453374343e-1 },
        std::pair< X, double >{ -5.25532409916328991e-1, 3.13706645877887047e-1 },
        std::pair< X, double >{ -1.83434642495649780e-1, 3.62683783378361768e-1 },
        std::pair< X, double >{  1.83434642495649780e-1, 3.62683783378361768e-1 },
        std::pair< X, double >{  5.25532409916328991e-1, 3.13706645877887047e-1 },
        std::pair< X, double >{  7.96666477413626728e-1, 2.22381034453374343e-1 },
        std::pair< X, double >{  9.60289856497536176e-1, 1.01228536290376689e-1 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

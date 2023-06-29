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

        std::pair< X, double >{ -8.61136311594052573e-1, 3.47854845137453683e-1 },
        std::pair< X, double >{ -3.39981043584856257e-1, 6.52145154862546206e-1 },
        std::pair< X, double >{  3.39981043584856257e-1, 6.52145154862546206e-1 },
        std::pair< X, double >{  8.61136311594052573e-1, 3.47854845137453683e-1 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

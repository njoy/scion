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

        std::pair< X, double >{ -0.9602898564975362, 0.1012285362903767 },
        std::pair< X, double >{ -0.7966664774136267, 0.2223810344533743 },
        std::pair< X, double >{ -0.5255324099163290, 0.3137066458778871 },
        std::pair< X, double >{ -0.1834346424956498, 0.3626837833783618 },
        std::pair< X, double >{  0.1834346424956498, 0.3626837833783618 },
        std::pair< X, double >{  0.5255324099163290, 0.3137066458778871 },
        std::pair< X, double >{  0.7966664774136267, 0.2223810344533743 },
        std::pair< X, double >{  0.9602898564975362, 0.1012285362903767 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

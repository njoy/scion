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

        std::pair< X, double >{ -0.949107912342759, 0.129484966168870 },
        std::pair< X, double >{ -0.741531185599394, 0.279705391489277 },
        std::pair< X, double >{ -0.405845151377397, 0.381830050505119 },
        std::pair< X, double >{  0.000000000000000, 0.417959183673469 },
        std::pair< X, double >{  0.405845151377397, 0.381830050505119 },
        std::pair< X, double >{  0.741531185599394, 0.279705391489277 },
        std::pair< X, double >{  0.949107912342759, 0.129484966168870 } };
      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

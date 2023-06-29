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

        std::pair< X, double >{ -9.32469514203152050e-1, 1.71324492379169746e-1 },
        std::pair< X, double >{ -6.61209386466264482e-1, 3.60761573048138939e-1 },
        std::pair< X, double >{ -2.38619186083196932e-1, 4.67913934572691370e-1 },
        std::pair< X, double >{  2.38619186083196932e-1, 4.67913934572691370e-1 },
        std::pair< X, double >{  6.61209386466264482e-1, 3.60761573048138939e-1 },
        std::pair< X, double >{  9.32469514203152050e-1, 1.71324492379169746e-1 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_8
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_8

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
   *  @brief The Gauss-Lobatto 8-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 13 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLobatto< 8, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 8, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 8, X, Y >, X, Y >;

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

        std::pair< X, double >{ -1.000000000000000e+0, 3.571428571428571e-2 },
        std::pair< X, double >{ -8.717401485096066e-1, 2.107042271435062e-1 },
        std::pair< X, double >{ -5.917001814331423e-1, 3.411226924835043e-1 },
        std::pair< X, double >{ -2.092992179024789e-1, 4.124587946587038e-1 },
        std::pair< X, double >{  2.092992179024789e-1, 4.124587946587038e-1 },
        std::pair< X, double >{  5.917001814331423e-1, 3.411226924835043e-1 },
        std::pair< X, double >{  8.717401485096066e-1, 2.107042271435062e-1 },
        std::pair< X, double >{  1.000000000000000e+0, 3.571428571428571e-2 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

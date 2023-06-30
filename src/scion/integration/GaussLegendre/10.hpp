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

        std::pair< X, double >{ -9.73906528517171743e-1, 6.66713443086880686e-2 },
        std::pair< X, double >{ -8.65063366688984536e-1, 1.49451349150580365e-1 },
        std::pair< X, double >{ -6.79409568299024436e-1, 2.19086362515982014e-1 },
        std::pair< X, double >{ -4.33395394129247213e-1, 2.69266719309996516e-1 },
        std::pair< X, double >{ -1.48874338981631216e-1, 2.95524224714752981e-1 },
        std::pair< X, double >{  1.48874338981631216e-1, 2.95524224714752981e-1 },
        std::pair< X, double >{  4.33395394129247213e-1, 2.69266719309996516e-1 },
        std::pair< X, double >{  6.79409568299024436e-1, 2.19086362515982014e-1 },
        std::pair< X, double >{  8.65063366688984536e-1, 1.49451349150580365e-1 },
        std::pair< X, double >{  9.73906528517171743e-1, 6.66713443086880686e-2 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

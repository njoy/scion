#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_16
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_16

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
   *  @brief The Gauss-Legendre 16-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLegendre< 16, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 16, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 16, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 16; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 16 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 16 > pairs = {

        std::pair< X, double >{ -9.89400934991649939e-1, 2.71524594117540374e-2 },
        std::pair< X, double >{ -9.44575023073232600e-1, 6.22535239386477063e-2 },
        std::pair< X, double >{ -8.65631202387831755e-1, 9.51585116824925914e-2 },
        std::pair< X, double >{ -7.55404408355002999e-1, 1.24628971255534030e-1 },
        std::pair< X, double >{ -6.17876244402643771e-1, 1.49595988816576764e-1 },
        std::pair< X, double >{ -4.58016777657227370e-1, 1.69156519395002619e-1 },
        std::pair< X, double >{ -2.81603550779258915e-1, 1.82603415044923612e-1 },
        std::pair< X, double >{ -9.50125098376374544e-2, 1.89450610455068585e-1 },
        std::pair< X, double >{  9.50125098376374544e-2, 1.89450610455068585e-1 },
        std::pair< X, double >{  2.81603550779258915e-1, 1.82603415044923612e-1 },
        std::pair< X, double >{  4.58016777657227370e-1, 1.69156519395002619e-1 },
        std::pair< X, double >{  6.17876244402643771e-1, 1.49595988816576764e-1 },
        std::pair< X, double >{  7.55404408355002999e-1, 1.24628971255534030e-1 },
        std::pair< X, double >{  8.65631202387831755e-1, 9.51585116824925914e-2 },
        std::pair< X, double >{  9.44575023073232600e-1, 6.22535239386477063e-2 },
        std::pair< X, double >{  9.89400934991649939e-1, 2.71524594117540374e-2 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

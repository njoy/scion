#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_32
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_32

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
   *  @brief The Gauss-Lobatto 32-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLobatto< 32, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 32, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 32, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 32; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 32 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 32 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 2.016129032258064e-3 },
        std::pair< X, double >{ -9.926089339727614e-1, 1.239810650137389e-2 },
        std::pair< X, double >{ -9.752946904827092e-1, 2.219955288929197e-2 },
        std::pair< X, double >{ -9.482848384172323e-1, 3.177513541091542e-2 },
        std::pair< X, double >{ -9.118499390637319e-1, 4.103420158606278e-2 },
        std::pair< X, double >{ -8.663524760126755e-1, 4.988527133622116e-2 },
        std::pair< X, double >{ -8.122447317774423e-1, 5.824049724805580e-2 },
        std::pair< X, double >{ -7.500644939366747e-1, 6.601687725715451e-2 },
        std::pair< X, double >{ -6.804297556155509e-1, 7.313713960267897e-2 },
        std::pair< X, double >{ -6.040325871484211e-1, 7.953052569210632e-2 },
        std::pair< X, double >{ -5.216322628815653e-1, 8.513349794966829e-2 },
        std::pair< X, double >{ -4.340477172018469e-1, 8.989037295735780e-2 },
        std::pair< X, double >{ -3.421494065388815e-1, 9.375387554681380e-2 },
        std::pair< X, double >{ -2.468506588502053e-1, 9.668560894800261e-2 },
        std::pair< X, double >{ -1.490985968136475e-1, 9.865643654076174e-2 },
        std::pair< X, double >{ -4.986472504659326e-2, 9.964677150127674e-2 },
        std::pair< X, double >{  4.986472504659326e-2, 9.964677150127674e-2 },
        std::pair< X, double >{  1.490985968136475e-1, 9.865643654076174e-2 },
        std::pair< X, double >{  2.468506588502053e-1, 9.668560894800261e-2 },
        std::pair< X, double >{  3.421494065388815e-1, 9.375387554681380e-2 },
        std::pair< X, double >{  4.340477172018469e-1, 8.989037295735780e-2 },
        std::pair< X, double >{  5.216322628815653e-1, 8.513349794966829e-2 },
        std::pair< X, double >{  6.040325871484211e-1, 7.953052569210632e-2 },
        std::pair< X, double >{  6.804297556155509e-1, 7.313713960267897e-2 },
        std::pair< X, double >{  7.500644939366747e-1, 6.601687725715451e-2 },
        std::pair< X, double >{  8.122447317774423e-1, 5.824049724805580e-2 },
        std::pair< X, double >{  8.663524760126755e-1, 4.988527133622116e-2 },
        std::pair< X, double >{  9.118499390637319e-1, 4.103420158606278e-2 },
        std::pair< X, double >{  9.482848384172323e-1, 3.177513541091542e-2 },
        std::pair< X, double >{  9.752946904827092e-1, 2.219955288929197e-2 },
        std::pair< X, double >{  9.926089339727614e-1, 1.239810650137389e-2 },
        std::pair< X, double >{  1.000000000000000e+0, 2.016129032258064e-3 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

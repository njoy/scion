#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_32
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_32

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
   *  @brief The Gauss-Legendre 32-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 63 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLegendre< 32, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 32, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 32, X, Y >, X, Y >;

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

        std::pair< X, double >{ -9.97263861849481570e-1, 7.01861000946929839e-3 },
        std::pair< X, double >{ -9.85611511545268382e-1, 1.62743947309059653e-2 },
        std::pair< X, double >{ -9.64762255587506390e-1, 2.53920653092624266e-2 },
        std::pair< X, double >{ -9.34906075937739667e-1, 3.42738629130216257e-2 },
        std::pair< X, double >{ -8.96321155766052202e-1, 4.28358980222264263e-2 },
        std::pair< X, double >{ -8.49367613732569970e-1, 5.09980592623762441e-2 },
        std::pair< X, double >{ -7.94483795967942386e-1, 5.86840934785357038e-2 },
        std::pair< X, double >{ -7.32182118740289711e-1, 6.58222227763617523e-2 },
        std::pair< X, double >{ -6.63044266930215231e-1, 7.23457941088484491e-2 },
        std::pair< X, double >{ -5.87715757240762304e-1, 7.81938957870703111e-2 },
        std::pair< X, double >{ -5.06899908932229359e-1, 8.33119242269468457e-2 },
        std::pair< X, double >{ -4.21351276130635333e-1, 8.76520930044039082e-2 },
        std::pair< X, double >{ -3.31868602282127667e-1, 9.11738786957638631e-2 },
        std::pair< X, double >{ -2.39287362252137065e-1, 9.38443990808045664e-2 },
        std::pair< X, double >{ -1.44471961582796488e-1, 9.56387200792748332e-2 },
        std::pair< X, double >{ -4.83076656877383104e-2, 9.65400885147278121e-2 },
        std::pair< X, double >{  4.83076656877383104e-2, 9.65400885147278121e-2 },
        std::pair< X, double >{  1.44471961582796488e-1, 9.56387200792748332e-2 },
        std::pair< X, double >{  2.39287362252137065e-1, 9.38443990808045664e-2 },
        std::pair< X, double >{  3.31868602282127667e-1, 9.11738786957638631e-2 },
        std::pair< X, double >{  4.21351276130635333e-1, 8.76520930044039082e-2 },
        std::pair< X, double >{  5.06899908932229359e-1, 8.33119242269468457e-2 },
        std::pair< X, double >{  5.87715757240762304e-1, 7.81938957870703111e-2 },
        std::pair< X, double >{  6.63044266930215231e-1, 7.23457941088484491e-2 },
        std::pair< X, double >{  7.32182118740289711e-1, 6.58222227763617523e-2 },
        std::pair< X, double >{  7.94483795967942386e-1, 5.86840934785357038e-2 },
        std::pair< X, double >{  8.49367613732569970e-1, 5.09980592623762441e-2 },
        std::pair< X, double >{  8.96321155766052202e-1, 4.28358980222264263e-2 },
        std::pair< X, double >{  9.34906075937739667e-1, 3.42738629130216257e-2 },
        std::pair< X, double >{  9.64762255587506390e-1, 2.53920653092624266e-2 },
        std::pair< X, double >{  9.85611511545268382e-1, 1.62743947309059653e-2 },
        std::pair< X, double >{  9.97263861849481570e-1, 7.01861000946929839e-3 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_GAUSSLOBATTO_64
#define NJOY_SCION_INTEGRATION_GAUSSLOBATTO_64

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
   *  @brief The Gauss-Lobatto 64-point quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 61 or less exactly.
   */
  template< typename X, typename Y >
  class GaussLobatto< 64, X, Y > :
    public GaussQuadratureBase< GaussLobatto< 64, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLobatto< 64, X, Y >, X, Y >;

    /* fields */

  public:

    /* methods */

    /**
     *  @brief Return the number of points used in the quadrature rule
     */
    static constexpr const int number() noexcept { return 64; }

    /**
     *  @brief Return the points and weights in the quadrature rule
     */
    static const std::array< std::pair< X, double >, 64 >& pairs() {

      static constexpr const std::array< std::pair< X, double >, 64 > pairs = {

        std::pair< X, double >{ -1.000000000000000e+0, 4.960317460317459e-4 },
        std::pair< X, double >{ -9.981798715021633e-1, 3.056008244912453e-3 },
        std::pair< X, double >{ -9.939027267030572e-1, 5.496016203817178e-3 },
        std::pair< X, double >{ -9.871926766027402e-1, 7.921289790046592e-3 },
        std::pair< X, double >{ -9.780666628313961e-1, 1.032700236681532e-2 },
        std::pair< X, double >{ -9.665471103690992e-1, 1.270739919745473e-2 },
        std::pair< X, double >{ -9.526622357886629e-1, 1.505668398796151e-2 },
        std::pair< X, double >{ -9.364460274756342e-1, 1.736911638454221e-2 },
        std::pair< X, double >{ -9.179381735102816e-1, 1.963904072324173e-2 },
        std::pair< X, double >{ -8.971839678458501e-1, 2.186090351151806e-2 },
        std::pair< X, double >{ -8.742342006576275e-1, 2.402926814402381e-2 },
        std::pair< X, double >{ -8.491450345429910e-1, 2.613882861433843e-2 },
        std::pair< X, double >{ -8.219778673075171e-1, 2.818442266584848e-2 },
        std::pair< X, double >{ -7.927991818262081e-1, 3.016104449908946e-2 },
        std::pair< X, double >{ -7.616803834081199e-1, 3.206385705772706e-2 },
        std::pair< X, double >{ -7.286976250888370e-1, 3.388820388412540e-2 },
        std::pair< X, double >{ -6.939316212907048e-1, 3.562962052448951e-2 },
        std::pair< X, double >{ -6.574674503129765e-1, 3.728384545980112e-2 },
        std::pair< X, double >{ -6.193943461384316e-1, 3.884683053780769e-2 },
        std::pair< X, double >{ -5.798054800677184e-1, 4.031475088156024e-2 },
        std::pair< X, double >{ -5.387977327168004e-1, 4.168401425080197e-2 },
        std::pair< X, double >{ -4.964714569360578e-1, 4.295126983360182e-2 },
        std::pair< X, double >{ -4.529302322315812e-1, 4.411341644689254e-2 },
        std::pair< X, double >{ -4.082806112898540e-1, 4.516761012594769e-2 },
        std::pair< X, double >{ -3.626318592262618e-1, 4.611127108428907e-2 },
        std::pair< X, double >{ -3.160956861956258e-1, 4.694209002702834e-2 },
        std::pair< X, double >{ -2.687859740191700e-1, 4.765803380222065e-2 },
        std::pair< X, double >{ -2.208184974969535e-1, 4.825735037641456e-2 },
        std::pair< X, double >{ -1.723106410877930e-1, 4.873857312223322e-2 },
        std::pair< X, double >{ -1.233811116500280e-1, 4.910052440750132e-2 },
        std::pair< X, double >{ -7.414964794611592e-2, 4.934231847713963e-2 },
        std::pair< X, double >{ -2.473672762195872e-2, 4.946336362077666e-2 },
        std::pair< X, double >{  2.473672762195872e-2, 4.946336362077666e-2 },
        std::pair< X, double >{  7.414964794611592e-2, 4.934231847713963e-2 },
        std::pair< X, double >{  1.233811116500280e-1, 4.910052440750132e-2 },
        std::pair< X, double >{  1.723106410877930e-1, 4.873857312223322e-2 },
        std::pair< X, double >{  2.208184974969535e-1, 4.825735037641456e-2 },
        std::pair< X, double >{  2.687859740191700e-1, 4.765803380222065e-2 },
        std::pair< X, double >{  3.160956861956258e-1, 4.694209002702834e-2 },
        std::pair< X, double >{  3.626318592262618e-1, 4.611127108428907e-2 },
        std::pair< X, double >{  4.082806112898540e-1, 4.516761012594769e-2 },
        std::pair< X, double >{  4.529302322315812e-1, 4.411341644689254e-2 },
        std::pair< X, double >{  4.964714569360578e-1, 4.295126983360182e-2 },
        std::pair< X, double >{  5.387977327168004e-1, 4.168401425080197e-2 },
        std::pair< X, double >{  5.798054800677184e-1, 4.031475088156024e-2 },
        std::pair< X, double >{  6.193943461384316e-1, 3.884683053780769e-2 },
        std::pair< X, double >{  6.574674503129765e-1, 3.728384545980112e-2 },
        std::pair< X, double >{  6.939316212907048e-1, 3.562962052448951e-2 },
        std::pair< X, double >{  7.286976250888370e-1, 3.388820388412540e-2 },
        std::pair< X, double >{  7.616803834081199e-1, 3.206385705772706e-2 },
        std::pair< X, double >{  7.927991818262081e-1, 3.016104449908946e-2 },
        std::pair< X, double >{  8.219778673075171e-1, 2.818442266584848e-2 },
        std::pair< X, double >{  8.491450345429910e-1, 2.613882861433843e-2 },
        std::pair< X, double >{  8.742342006576275e-1, 2.402926814402381e-2 },
        std::pair< X, double >{  8.971839678458501e-1, 2.186090351151806e-2 },
        std::pair< X, double >{  9.179381735102816e-1, 1.963904072324173e-2 },
        std::pair< X, double >{  9.364460274756342e-1, 1.736911638454221e-2 },
        std::pair< X, double >{  9.526622357886629e-1, 1.505668398796151e-2 },
        std::pair< X, double >{  9.665471103690992e-1, 1.270739919745473e-2 },
        std::pair< X, double >{  9.780666628313961e-1, 1.032700236681532e-2 },
        std::pair< X, double >{  9.871926766027402e-1, 7.921289790046592e-3 },
        std::pair< X, double >{  9.939027267030572e-1, 5.496016203817178e-3 },
        std::pair< X, double >{  9.981798715021633e-1, 3.056008244912453e-3 },
        std::pair< X, double >{  1.000000000000000e+0, 4.960317460317459e-4 } };

        return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

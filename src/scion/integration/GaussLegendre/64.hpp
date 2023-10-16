#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_64
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE_64

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
   *  @brief The Gauss-Legendre 64-point quadrature rule
   */
  template< typename X, typename Y >
  class GaussLegendre< 64, X, Y > :
    public GaussQuadratureBase< GaussLegendre< 64, X, Y >, X, Y > {

    /* type aliases */
    using Parent = GaussQuadratureBase< GaussLegendre< 64, X, Y >, X, Y >;

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

        std::pair< X, double >{ -9.99305041735772170e-1, 1.78328072169421517e-3 },
        std::pair< X, double >{ -9.96340116771955220e-1, 4.14703326056292329e-3 },
        std::pair< X, double >{ -9.91013371476744287e-1, 6.50445796897965427e-3 },
        std::pair< X, double >{ -9.83336253884625977e-1, 8.84675982636439102e-3 },
        std::pair< X, double >{ -9.73326827789910975e-1, 1.11681394601314665e-2 },
        std::pair< X, double >{ -9.61008799652053769e-1, 1.34630478967182315e-2 },
        std::pair< X, double >{ -9.46411374858402765e-1, 1.57260304760250824e-2 },
        std::pair< X, double >{ -9.29569172131939570e-1, 1.79517157756973016e-2 },
        std::pair< X, double >{ -9.10522137078502825e-1, 2.01348231535300945e-2 },
        std::pair< X, double >{ -8.89315445995114140e-1, 2.22701738083830071e-2 },
        std::pair< X, double >{ -8.65999398154092770e-1, 2.43527025687108531e-2 },
        std::pair< X, double >{ -8.40629296252580316e-1, 2.63774697150546272e-2 },
        std::pair< X, double >{ -8.13265315122797539e-1, 2.83396726142597019e-2 },
        std::pair< X, double >{ -7.83972358943341385e-1, 3.02346570724024953e-2 },
        std::pair< X, double >{ -7.52819907260531940e-1, 3.20579283548514532e-2 },
        std::pair< X, double >{ -7.19881850171610771e-1, 3.38051618371417867e-2 },
        std::pair< X, double >{ -6.85236313054233270e-1, 3.54722132568823234e-2 },
        std::pair< X, double >{ -6.48965471254657311e-1, 3.70551285402401509e-2 },
        std::pair< X, double >{ -6.11155355172393278e-1, 3.85501531786155913e-2 },
        std::pair< X, double >{ -5.71895646202634000e-1, 3.99537411327203495e-2 },
        std::pair< X, double >{ -5.31279464019894565e-1, 4.12625632426234859e-2 },
        std::pair< X, double >{ -4.89403145707052956e-1, 4.24735151236535977e-2 },
        std::pair< X, double >{ -4.46366017253464087e-1, 4.35837245293234643e-2 },
        std::pair< X, double >{ -4.02270157963991626e-1, 4.45905581637565454e-2 },
        std::pair< X, double >{ -3.57220158337668126e-1, 4.54916279274181143e-2 },
        std::pair< X, double >{ -3.11322871990210970e-1, 4.62847965813143747e-2 },
        std::pair< X, double >{ -2.64687162208767424e-1, 4.69681828162099996e-2 },
        std::pair< X, double >{ -2.17423643740007083e-1, 4.75401657148303014e-2 },
        std::pair< X, double >{ -1.69644420423992803e-1, 4.79993885964583172e-2 },
        std::pair< X, double >{ -1.21462819296120558e-1, 4.83447622348029543e-2 },
        std::pair< X, double >{ -7.29931217877990424e-2, 4.85754674415034560e-2 },
        std::pair< X, double >{ -2.43502926634244291e-2, 4.86909570091397514e-2 },
        std::pair< X, double >{  2.43502926634244291e-2, 4.86909570091397514e-2 },
        std::pair< X, double >{  7.29931217877990424e-2, 4.85754674415034560e-2 },
        std::pair< X, double >{  1.21462819296120558e-1, 4.83447622348029543e-2 },
        std::pair< X, double >{  1.69644420423992803e-1, 4.79993885964583172e-2 },
        std::pair< X, double >{  2.17423643740007083e-1, 4.75401657148303014e-2 },
        std::pair< X, double >{  2.64687162208767424e-1, 4.69681828162099996e-2 },
        std::pair< X, double >{  3.11322871990210970e-1, 4.62847965813143747e-2 },
        std::pair< X, double >{  3.57220158337668126e-1, 4.54916279274181143e-2 },
        std::pair< X, double >{  4.02270157963991626e-1, 4.45905581637565454e-2 },
        std::pair< X, double >{  4.46366017253464087e-1, 4.35837245293234643e-2 },
        std::pair< X, double >{  4.89403145707052956e-1, 4.24735151236535977e-2 },
        std::pair< X, double >{  5.31279464019894565e-1, 4.12625632426234859e-2 },
        std::pair< X, double >{  5.71895646202634000e-1, 3.99537411327203495e-2 },
        std::pair< X, double >{  6.11155355172393278e-1, 3.85501531786155913e-2 },
        std::pair< X, double >{  6.48965471254657311e-1, 3.70551285402401509e-2 },
        std::pair< X, double >{  6.85236313054233270e-1, 3.54722132568823234e-2 },
        std::pair< X, double >{  7.19881850171610771e-1, 3.38051618371417867e-2 },
        std::pair< X, double >{  7.52819907260531940e-1, 3.20579283548514532e-2 },
        std::pair< X, double >{  7.83972358943341385e-1, 3.02346570724024953e-2 },
        std::pair< X, double >{  8.13265315122797539e-1, 2.83396726142597019e-2 },
        std::pair< X, double >{  8.40629296252580316e-1, 2.63774697150546272e-2 },
        std::pair< X, double >{  8.65999398154092770e-1, 2.43527025687108531e-2 },
        std::pair< X, double >{  8.89315445995114140e-1, 2.22701738083830071e-2 },
        std::pair< X, double >{  9.10522137078502825e-1, 2.01348231535300945e-2 },
        std::pair< X, double >{  9.29569172131939570e-1, 1.79517157756973016e-2 },
        std::pair< X, double >{  9.46411374858402765e-1, 1.57260304760250824e-2 },
        std::pair< X, double >{  9.61008799652053769e-1, 1.34630478967182315e-2 },
        std::pair< X, double >{  9.73326827789910975e-1, 1.11681394601314665e-2 },
        std::pair< X, double >{  9.83336253884625977e-1, 8.84675982636439102e-3 },
        std::pair< X, double >{  9.91013371476744287e-1, 6.50445796897965427e-3 },
        std::pair< X, double >{  9.96340116771955220e-1, 4.14703326056292329e-3 },
        std::pair< X, double >{  9.99305041735772170e-1, 1.78328072169421517e-3 } };

      return pairs;
    }

    using Parent::operator();
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_MATH_PROCESSEDDATA
#define NJOY_SCION_MATH_PROCESSEDDATA

// system includes
#include <vector>

// other includes

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @struct
   *  @brief A helper struct for tabulated data
   */
  template < typename X, typename Y >
  struct ProcessedData {

    std::vector< X > x;
    std::vector< Y > y;
    std::vector< std::size_t > boundaries;
    std::vector< interpolation::InterpolationType > interpolants;
    bool linearised;
    bool curated;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_GAUSSLEGENDRE
#define NJOY_SCION_INTEGRATION_GAUSSLEGENDRE

// system includes
#include <array>

// other includes
#include "scion/integration/GaussQuadratureBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Points and weights for an N-point Gauss-Legendre quadrature rule
   */
  template< int N, typename X, typename Y = X >
  class GaussLegendre;

  #include "scion/integration/GaussLegendre/2.hpp"
  #include "scion/integration/GaussLegendre/7.hpp"

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_QUADRATURE
#define NJOY_SCION_INTEGRATION_QUADRATURE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Points and weights for an N-point Gauss-Legendre quadrature rule
   */
  template< int N, typename X, typename Y = X >
  class GaussLegendre;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

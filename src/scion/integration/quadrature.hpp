#ifndef NJOY_SCION_INTEGRATION_QUADRATURE
#define NJOY_SCION_INTEGRATION_QUADRATURE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief An N-point Gauss-Legendre quadrature rule
   *
   *  This quadrature rule integrates polynomials of order 2N-1 or less exactly.
   */
  template< int N, typename X, typename Y = X >
  class GaussLegendre;

  /**
   *  @class
   *  @brief An N-point Gauss-Lobatto quadrature rule (also known as Gauss-Radau)
   *
   *  This quadrature rule integrates polynomials of order 2N-3 or less exactly.
   */
  template< int N, typename X, typename Y = X >
  class GaussLobatto;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

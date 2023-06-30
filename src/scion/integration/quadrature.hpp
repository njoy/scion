#ifndef NJOY_SCION_INTEGRATION_QUADRATURE
#define NJOY_SCION_INTEGRATION_QUADRATURE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief An n-point Gauss-Legendre quadrature rule
   *
   *  A quadrature rule is an approximation of the definite integral of a
   *  function as a weighted sum of n function values at specified points within
   *  the domain of integration:
   *    integral[-1,+1] W(x) f(x) dx = sum[1,n] wi f(xi)
   *  with W(x) a weight function and xi and wi the nodes (or abscissa) and
   *  weights of the quadrature rule.
   *
   *  In Gauss-Legendre quadrature, the weight function used is W(x) = 1. In this
   *  case, the nodes of the n-point Gauss-Legendre rule are the roots of the
   *  Legendre polynomial of order n.
   *
   *  The nodes and weights used in these quadrature rules are calculated using
   *  numpy. See src/scion/integration/resources for the Jupyter notebook for 
   *  the code used to compute these values.
   *
   *  This quadrature rule integrates polynomials of order 2N-1 or less exactly.
   */
  template< int N, typename X, typename Y = X >
  class GaussLegendre;

  /**
   *  @class
   *  @brief An N-point Gauss-Lobatto quadrature rule (also known as Gauss-Radau)
   *
   *  A quadrature rule is an approximation of the definite integral of a
   *  function as a weighted sum of n function values at specified points within
   *  the domain of integration:
   *    integral[-1,+1] W(x) f(x) dx = sum[1,n] wi f(xi)
   *  with W(x) a weight function and xi and wi the nodes (or abscissa) and
   *  weights of the quadrature rule.
   *
   *  In Gauss-Lobatto quadrature, the end points of the integral are used as
   *  nodes in the quadrature rule. As with Gauss-Legendre quadrature,  the
   *  weight function used is W(x) = 1.
   *
   *  The nodes and weights used in these quadrature rules are calculated using
   *  scion. See src/scion/integration/resources for the Jupyter notebook for
   *  the code used to compute these values.
   *
   *  This quadrature rule integrates polynomials of order 2N-3 or less exactly.
   */
  template< int N, typename X, typename Y = X >
  class GaussLobatto;

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

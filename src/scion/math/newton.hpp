#ifndef NJOY_SCION_MATH_NEWTON
#define NJOY_SCION_MATH_NEWTON

// system includes
#include <iostream>
// other includes
#include "scion/math/compare.hpp"

namespace njoy {
namespace scion {
namespace math {

/** @brief Apply the Newton-Raphson method for root estimation
 *
 *  The Newton-Raphson method is used to calculate the root of a function f(x)
 *  provided that an estinate of the root is given. The method works by
 *  iteratively calculating new estimates to the root until it converges. The
 *  estimate of the root in iteration n+1 is given as:
 *    root(n+1) = root(n) - f(root(n)) / df/dx(root(n))
 *
 *  By default, this method will perform at the leat the number of requested
 *  iterations (by default 5 iterations) if the root does not converge (as
 *  determined by the isClose function).
 *
 *  Caveat: this method can break down when df/dx(root(n)) is close to zero.
 *
 *  @param[in] estimate      the estimate of the root
 *  @param[in] functor       the function f(x)
 *  @param[in] derivative    the derivative of the function f(x)
 *  @param[in] iterations    the number of iterations if the root does not
 *                           converge (by default 5 iterations)
 */
template < typename X, typename Functor, typename Derivative >
X newton( X estimate, Functor&& functor, Derivative&& derivative,
          int iterations = 5 ) noexcept {

  X root = estimate - functor( estimate ) / derivative( estimate );
  while ( ( ! isClose( root, estimate ) ) || ( iterations != 0 ) ) {

    std::swap( estimate, root );
    root = estimate - functor( estimate ) / derivative( estimate );
    --iterations;
  }
  return root;
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

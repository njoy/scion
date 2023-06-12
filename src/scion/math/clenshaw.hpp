#ifndef NJOY_SCION_MATH_CLENSHAW
#define NJOY_SCION_MATH_CLENSHAW

// system includes
#include <functional>

// other includes

namespace njoy {
namespace scion {
namespace math {

/** @brief Clenshaw recursion scheme using iterators
 *
 *  The Clenshaw recursion scheme is an elegant and efficient way to
 *  evaluate a sum of coefficients times functions that obey a recursion
 *  formula (such as Legendre polynomials).
 *
 *  Consider a function defined as follows:
 *
 *    y = c_n * F_n(x) + c_(n - 1) * F_(n - 1)(x) + ... + c_0 * F_0(x)
 *
 *  with F_(k + 1)(x) = a(k, x) * F_k(x) + b(k, x) * F_(k - 1)(x)
 *
 *  We now define the values y_k:
 *
 *    y_(n + 1) = y_(n + 2) = 0.0
 *    y_k = a(k, x) * y_(k+1) + b(k + 1, x) * y_(k + 2) + c_k  for k = n .. 1
 *
 *  Once we know y_2 and y_1, it can be shown that the value of y will be equal to:
 *
 *    y = b(1, x) * F_0(x) * y_2 + F_1(x) * y_1 + c_0 * F_0(x)
 *
 *  Source: Numerical recipes - Third edition, p222-223
 *
 *  The main reason for using the Clenshaw recursion scheme is computational
 *  efficiency.
 *
 *  @param[in] first   an input iterator to the initial position in a sequence
 *                     (must be the highest order coefficient)
 *  @param[in] last    an input iterator to the final position in a sequence
 *  @param[in] a       the function a(k, x)
 *  @param[in] b       the function b(k, x)
 *  @param[in] f0      the value of F_0(x)
 *  @param[in] f1      the value of F_1(x)
 *  @param[in] x       the value of X
 */
template < typename X, typename Y = X, typename Iter,
           typename FunctorA = std::function< Y ( unsigned int, X&& ) >,
           typename FunctorB = std::function< Y ( unsigned int, X&& ) > >
Y clenshaw( Iter first, Iter last, FunctorA&& a, FunctorB&& b,
            const Y& f0, const Y& f1, const X& x ) noexcept {

  unsigned int n = std::distance(first, last) - 1;
  if (0 != n) {

    Y y = Y(0.0);
    Y y2 = y;
    Y y1 = *first;
    ++first;
    --n;
    --last;
    for ( ; first != last; ++first ) {

      y = a(n, x) * y1 + b(n + 1, x) * y2 + *first;
      std::swap( y2, y1 );
      std::swap( y1, y );
      --n;
    }
    return b(1, x) * f0 * y2 + f1 * y1 + *first * f0;
  }
  else {

    return *first;
  }
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

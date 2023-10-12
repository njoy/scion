#ifndef NJOY_SCION_MATH_LEGENDRE
#define NJOY_SCION_MATH_LEGENDRE

// system includes

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace scion {
namespace math {

/** @brief Evaluate a Chebyshev polynomial of order n
 *
 *  @param[in] n    the degree of the Chebyshev polynomial
 *  @param[in] x    the value of X
 */
template < typename X, typename Y = X >
Y chebyshev( unsigned int n, const X& x ) {

  if ( ( x < -1 ) || ( x > 1 ) ) {

    Log::error( "Chebyshev polynomials are defined for x values in the [-1,1] interval" );
    Log::info( "The value of x requested: {}", x );
    throw std::exception();
  }

  Y t0 = Y( 1. );
  Y t = Y( x );

  if ( n == 0 ) {

    return t0;
  }

  unsigned int l = 1;
  while ( l < n ) {

    std::swap( t0, t );
    t = ( static_cast< Y >( 2 ) * x * t0 - t );
    ++l;
  }

  return t;
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

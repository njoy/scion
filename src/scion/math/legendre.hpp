#ifndef NJOY_SCION_MATH_LEGENDRE
#define NJOY_SCION_MATH_LEGENDRE

// system includes

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace scion {
namespace math {

/** @brief Evaluate a Legendre polynomial of order n
 *
 *  @param[in] n    the order of the Legendre polynomial
 *  @param[in] x    the value of X
 */
template < typename X, typename Y = X >
Y legendre( unsigned int n, const X& x ) {

  if ( ( x < -1 ) || ( x > 1 ) ) {

    Log::error( "Legendre polynomials are defined for x values in the [-1,1] interval" );
    Log::info( "The order of the Legendre polynomial requested: {}", n );
    Log::info( "The value of x requested: {}", x );
    throw std::exception();
  }

  Y p0 = Y( 1. );
  Y p = Y( x );

  if ( n == 0 ) {

    return p0;
  }

  unsigned int l = 1;
  while ( l < n ) {

    std::swap( p0, p );
    p = ( static_cast< Y >( 2 * l + 1 ) * x * p0 - l * p ) / static_cast< Y >( l + 1 );
    ++l;
  }

  return p;
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

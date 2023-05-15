template < typename Functor > static std::vector< Y >
calculateCoefficients( X lower, X upper, Functor&& function, unsigned int order ) {

  std::vector< Y > coefficients( order + 1, Y( 0. ) );
  unsigned int n = order + 1;
  const double pi = std::acos( -1. );

  // transform x in [-1, 1] to x' in [lower, upper]
  const auto transform = [lower, upper] ( const X& x ) {

    return ( x + X( 1 ) ) * ( upper - lower ) / X( 2 ) + lower;
  };

  // calculate values of function in zeros of Chebyshev polynomial of order n
  std::vector< Y > f;
  for ( unsigned int i = 0; i < n; ++i ) {

    f.emplace_back( function( transform( std::cos( pi * ( i + 0.5 ) / n ) ) ) );
  }

  // calculate the coefficients of the approximation
  for ( unsigned int i = 0; i < n; ++i ) {

    for ( unsigned int j = 0; j < n; ++j ) {

      coefficients[i] += f[j] * std::cos( pi * i * ( j + 0.5 ) / n );
    }
    coefficients[i] *= 2. / Y( n );
  }
  coefficients[0] *= 0.5;

  return coefficients;
}

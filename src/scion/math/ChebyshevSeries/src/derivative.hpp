/**
 *  @brief Return the derivative of the Chebyshev series
 *
 *  The derivative function of a Chebyshev series function is another
 *  Chebyshev series function. The coefficients of the new Chebyshev series
 *  are calculated using the derivative of a Chebyshev polynomial as a
 *  function of other Chebyshev polynomials:
 *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_1 ) if n is even
 *    d/dx T_n = 2 n ( T_(n-1) + T_(n-3) + ... + T_2 ) + n T_0 if n is odd
 *
 *  This relation can be proven by mathematical induction.
 *
 *  The derivative function is defined over the same domain as the
 *  original function.
 */
ChebyshevSeries derivative() const {

  const unsigned int order = this->order();
  if ( 0 == order ) {

    return ChebyshevSeries( { Y( 0. ) } );
  }
  else {

    std::vector< Y > derivative( order, Y( 0. ) );
    for ( unsigned int i = 0; i < order; ++i ) {

      const Y a = static_cast< Y >( 2 * ( i + 1 ) ) * this->coefficients()[i + 1];
      int j = static_cast< int >( i );
      while ( 0 < j ) {

        derivative[j] += a;
        j -= 2;
      }
      if ( 0 == j ) {

        derivative[0] += static_cast< Y >( i + 1 ) * this->coefficients()[i + 1];
      }
    }

    return ChebyshevSeries( std::move( derivative ) );
  }
}

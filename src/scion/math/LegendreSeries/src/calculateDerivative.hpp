/**
 *  @brief Return the derivative of the Legendre series
 *
 *  The derivative function of a Legendre series function is another
 *  Legendre series function. The coefficients of the new Legendre series
 *  are calculated using the derivative of a Legendre polynomial as a
 *  function of other Legendre polynomials:
 *    d/dx P_(n + 1) = (2 * n + 1) * P_n + (2 * (n - 2) + 1) * P_(n - 2) + ...
 *  knowing that:
 *    d/dx P_0 = 0.0
 *    d/dx P_1 = P_0
 *
 *  This formula can be derived using the following property of Legendre
 *  polynomials:
 *    ( 2 * n + 1 ) * P_n = d/dx P_(n + 1) - d/dx P_(n - 1)
 *
 *  The derivative function is defined over the same domain as the
 *  original function.
 */
LegendreSeries calculateDerivative() const {

  const unsigned int order = this->order();
  std::vector< Y > derivative( order, Y( 0. ) );
  for ( unsigned int i = 0; i < order; ++i ) {

    const Y a = this->coefficients()[i + 1];
    int j = static_cast< int >( i );
    while ( 0 <= j ) {

      derivative[j] += static_cast< Y >( 2 * j + 1 ) * a;
      j -= 2;
    }
  }

  return LegendreSeries( std::move( derivative ) );
}

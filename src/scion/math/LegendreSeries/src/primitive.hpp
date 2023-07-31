/**
 *  @brief Return the primitive (or antiderivative) of the Legendre series
 *
 *  The primitive or antiderivative of a Legendre series function is another
 *  Legendre series function. The coefficients of the new Legendre series
 *  are calculated using the integral of a Legendre polynomial as a
 *  function of other Legendre polynomials:
 *    int P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
 *
 *  The integrated series is defined so that the integral function for x = left
 *  equals 0.
 *
 *  @param[in] left    the left bound of the integral (default = 0)
 */
LegendreSeries primitive( const X& left = X( 0. ) ) const {

  unsigned int order = this->order();
  std::vector< Y > primitive( order + 2, Y( 0. ) );
  primitive[1] = this->coefficients()[0];
  for ( unsigned int i = 1; i < order + 1; ++i ) {

    auto c =  this->coefficients()[i] / Y( 2 * i + 1 );
    primitive[i + 1] += c;
    primitive[i - 1] -= c;
  }
  primitive[0] -= clenshawLegendre( primitive, left );

  return LegendreSeries( std::move( primitive ) );
}

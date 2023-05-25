/**
 *  @brief Return the primitive (or antiderivative) of the Chebyshev series
 *
 *  The primitive or antiderivative of a Chebyshev series function is another
 *  Chebyshev series function. The coefficients of the new Chebyshev series
 *  are calculated using the integral of a Chebyshev polynomial as a
 *  function of other Chebyshev polynomials:
 *    2 int T_n = T_(n + 1)/(n + 1) - T_(n - 1)/(n - 1)
 *
 *  The integrated series is defined so that the integral function for x = left
 *  equals 0.
 *
 *  @param[in] left    the left bound of the integral (default = 0)
 */
ChebyshevSeries calculatePrimitive( const X& left = X( 0. ) ) const {

  unsigned int order = this->order();
  std::vector< Y > primitive( order + 2, Y( 0. ) );
  primitive[1] = this->coefficients()[0];
  primitive[2] = Y( 0.25 ) * this->coefficients()[1];
  for ( unsigned int i = 2; i < order + 1; ++i ) {

    auto c =  Y( 0.5 ) * this->coefficients()[i];
    primitive[i + 1] += c / Y( i + 1 );
    primitive[i - 1] -= c / Y( i - 1 );
  }
  primitive[0] -= clenshawChebyshev( primitive, left );

  return ChebyshevSeries( std::move( primitive ) );
}

/**
 *  @brief Return the primitive (or antiderivative) of the Legendre series
 *
 *  The primitive or antiderivative of a Legendre series function is another
 *  Legendre series function. The coefficients of the new Legendre series
 *  are calculated using the integral of a Legendre polynomial as a
 *  function of other Legendre polynomials:
 *    int[-1,x] P_n = (P_(n + 1) - P_(n - 1))/(2 * n + 1)
 *
 *  The integral function is defined so that int[-1,-1] f(x) = 0.0.
 *
 *  Due to orthogonality of the Legendre polynomials, the integral between
 *  -1 and 1 is always equal to the coefficient of the P_0 polynomial
 *  multiplied by two.
 */
LegendreSeries primitive() const {

  unsigned int order = this->order();
  std::vector< Y > primitive( order + 2, Y( 0. ) );
  primitive[1] += this->coefficients()[0];
  for ( unsigned int i = 1; i < order + 1; ++i ) {

    auto c =  this->coefficients()[i] / Y( 2 * i + 1 );
    primitive[i + 1] += c;
    primitive[i - 1] -= c;
  }
  primitive[0] = Y( 0. );

  return LegendreSeries( std::move( primitive ) );
}

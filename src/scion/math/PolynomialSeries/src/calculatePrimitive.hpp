/**
 *  @brief Return the primitive (or antiderivative) of the polynomial series
 *
 *  The primitive or antiderivative of a polynomial series is another polynomial
 *  series: y -> int f(x) = c_0 + sum c_i/(i+1) x^(i+1)
 *
 *  The integrated series is defined so that the integral function for x = left
 *  equals 0.
 *
 *  The primitive function is defined over the same domain as the original
 *  series.
 *
 *  @param[in] left    the left bound of the integral (default = 0)
 */
PolynomialSeries calculatePrimitive( const X& left = X( 0. ) ) const {

  unsigned int order = this->order();
  std::vector< Y > primitive( order + 2, Y( 0. ) );
  for ( unsigned int i = 1; i < order + 2; ++i ) {

    primitive[i] = this->coefficients()[i-1] / Y( i );
  }
  primitive[0] -= horner( primitive, left );

  return PolynomialSeries( this->domain(), std::move( primitive ) );
}

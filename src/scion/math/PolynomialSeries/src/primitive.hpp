/**
 *  @brief Return the primitive (or antiderivative) of the polynomial series
 *
 *  The primitive or antiderivative of a polynomial series is another polynomial
 *  series: y -> int[a,x] f(x) = d + sum c_i/(i+1) x^(i+1)
 *  The value of d is defined so that the integral function for x = a = 0
 *  equals 0.
 *
 *  The primitive function is defined over the same domain as the original
 *  function.
 */
PolynomialSeries primitive() const {

  std::vector< Y > primitive = this->coefficients();
  primitive.insert( primitive.begin(), X( 0. ) );
  for ( unsigned int i = 1; i < primitive.size(); ++i ) {

    primitive[i] /= Y( i );
  }

  return PolynomialSeries( this->domain(), std::move( primitive ) );
}

/**
 *  @brief Return the derivative of the polynomial series
 *
 *  The first order derivative of a polynomial series is another polynomial
 *  series: y -> d/dx f(x) = sum i c_i x^(i-1) for i = 1 to n
 *
 *  The derivative function is defined over the same domain as the
 *  original function.
 */
PolynomialSeries derivative() const {

  if ( 0 == this->order() ) {

    return PolynomialSeries( this->domain(), { Y( 0. ) } );
  }
  else {

    std::vector< Y > derivative = this->coefficients();
    for ( unsigned int i = 1; i < derivative.size(); ++i ) {

      derivative[i] *= i;
    }
    derivative.erase( derivative.begin() );

    return PolynomialSeries( this->domain(), std::move( derivative ) );
  }
}
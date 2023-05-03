/**
 *  @brief Evaluate the function for a value of x
 *
 *  The Clenshaw recursion scheme is used for the evaluation of the series
 *  using the following recursion relation for Chebyshev polynomials:
 *
 *    P(n+2,x) = 2 x P(n+1,x) - P(n,x)
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  return math::clenshawChebyshev( this->coefficients(), x );
}

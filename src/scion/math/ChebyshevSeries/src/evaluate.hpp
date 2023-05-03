/**
 *  @brief Evaluate the function for a value of x
 *
 *  The Clenshaw recursion scheme is used for the evaluation of the series
 *  using the following recursion relation for Chebyshev polynomials:
 *
 *    T_(n+2) = 2 x T_(n+1) - T_n
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  return math::clenshawChebyshev( this->coefficients(), x );
}

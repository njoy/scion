/**
 *  @brief Evaluate the function for a value of x
 *
 *  The Clenshaw recursion scheme is used for the evaluation of the series
 *  using the following recursion relation for Legendre polynomials:
 *
 *    P(n+2,x) = (2k+1)/(k+1) x P(n+1,x) - k/(k+1) P(n,x)
 *
 *  An exception is thrown for values outside of the domain.
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  if ( ! this->isInside( x ) ) {

    Log::error( "Legendre polynomials are defined for x values in the [-1,1] interval" );
    Log::info( "The value of x requested: {}", x );
    throw std::exception();
  }

  auto a = [] ( unsigned int k, const X& x ) -> Y {

    return static_cast< Y >( 2 * k + 1 ) / static_cast< Y >( k + 1 ) * x;
  };
  auto b = [] ( unsigned int k, const X& x ) -> Y {

    return - static_cast< Y >( k ) / static_cast< Y >( k + 1 );
  };

  return math::clenshaw( this->coefficients().rbegin(),
                         this->coefficients().rend(),
                         a, b, 1., x, x );
}

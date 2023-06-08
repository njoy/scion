/**
 *  @brief Evaluate the function for a value of x
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

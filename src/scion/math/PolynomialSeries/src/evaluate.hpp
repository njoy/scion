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

  return math::horner( this->coefficients().rbegin(),
                       this->coefficients().rend(),
                       x );
}

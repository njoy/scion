/**
 *  @brief Evaluate the function for a value of x
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  if ( ! this->isInside( x ) ) {

    Log::error( "The value of x requested (x={}) is outside of the domain of the "
                "polynomial series", x );
    throw std::exception();
  }

  return math::horner( this->coefficients().rbegin(),
                       this->coefficients().rend(),
                       x );
}

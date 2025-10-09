/**
 *  @brief Evaluate the function for a value of x
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  if ( this->denominator().order() == 0 ) {

    return this->numerator()( x );
  }
  else {

    return this->numerator()( x ) / this->denominator()( x );
  }
}

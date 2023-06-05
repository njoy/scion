/**
 *  @brief Evaluate the approximated function for a value of x
 *
 *  Chebyshev function approximation only works well within the defined
 *  domain. Outside of the domain, the approximated function can quickly diverge.
 *  Range checking by the user is advised.
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  return this->series_( this->transform( x ) );
}

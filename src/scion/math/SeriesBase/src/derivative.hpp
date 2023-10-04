/**
 *  @brief Return the derivative of the Chebyshev series
 */
Derived derivative() const {

  const unsigned int order = this->order();
  if ( 0 == order ) {

    return Derived( { Y( 0. ) } );
  }
  else {

    return static_cast< const Derived* >( this )->calculateDerivative();
  }
}

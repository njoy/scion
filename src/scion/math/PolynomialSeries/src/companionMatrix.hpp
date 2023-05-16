Matrix< Y > companionMatrix( const Y& a ) const {

  // This does not check for order 0 or 1: this case is explicitly handled in the
  // roots( ... ) method.

  const unsigned int order = this->order();
  const Y scale = this->coefficients().back();

  Matrix< X > matrix( order, order );
  matrix.setZero();

  matrix( order - 1, 0 ) = - ( this->coefficients()[0] - a ) / scale;
  matrix( 0, 1 ) = Y( 1. );
  for ( unsigned int i = 1; i < order; ++i ) {

    matrix( order - 1, i ) = - this->coefficients()[i] / scale;
    if ( i + 1 < order ) {

      matrix( i, i + 1 ) = Y( 1. );
    }
  }

  return matrix;
}

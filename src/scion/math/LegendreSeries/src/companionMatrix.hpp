Matrix< Y > companionMatrixBoyd( const Y& a ) const {

  // Reference:
  // John P. Boyd
  // Computing the zeros, maxima and inflection points of Chebyshev, Legendre
  // and Fourier series: solving transcendental equations by spectral
  // interpolation and polynomial rootfinding
  // Journal of Engineering Mathematics volume 56, pages 203–219 (2006)
  // doi: 10.1007/s10665-006-9087-5

  // This does not check for order 0 or 1: this case is explicitly handled in the
  // roots( ... ) method.

  const unsigned int order = this->order();
  const Y scale = this->coefficients().back() * Y( 2 * order - 1 ) / Y( order );

  Matrix< X > matrix( order, order );
  matrix.setZero();

  matrix( order - 1, 0 ) = - ( this->coefficients().front() - a ) / scale;
  matrix( 0, 1 ) = Y( 1. );
  for ( unsigned int i = 1; i < order - 1; ++i ) {

    matrix( i, i - 1 ) = Y( i ) / Y( 2 * i + 1 );
    matrix( i, i + 1 ) = Y( i + 1 ) / Y( 2 * i + 1 );
    matrix( order - 1, i ) = - this->coefficients()[i] / scale;
  }
  matrix( order - 1, order - 2 ) += Y( order - 1 ) / Y( 2 * order - 1 );
  matrix( order - 1, order - 1 ) = - this->coefficients()[order - 1] / scale;

  matrix.transposeInPlace();
  matrix.reverseInPlace();

  return matrix;
}

Matrix< Y > companionMatrix( const Y& a ) const {

  // Reference: numpy

  // This does not check for order 0 or 1: this case is explicitly handled in the
  // roots( ... ) method.

  const unsigned int order = this->order();
  const Y scale = this->coefficients().back() * Y( 2 * order - 1 ) / Y( order );

  Matrix< X > matrix( order, order );
  matrix.setZero();

  for ( unsigned int i = 0; i < order - 1; ++i ) {

    matrix( i, i + 1 ) = Y( i + 1 ) / std::sqrt( Y( 2 * i + 1 ) * Y( 2 * i + 3 ) );
    matrix( i + 1, i ) = matrix( i, i + 1 );
  }
  matrix( order - 1, order - 2 ) = matrix( order - 2, order - 1 );

  matrix( order - 1, 0 ) -= ( this->coefficients().front() - a ) / scale
                            * std::sqrt( Y( 2 * order - 1 ) );
  for ( unsigned int i = 1; i < order; ++i ) {

    matrix( order - 1, i ) -= this->coefficients()[i] / scale
                              / std::sqrt( Y( 2 * i + 1 ) )
                              * std::sqrt( Y( 2 * order - 1 ) );
  }

  matrix.transposeInPlace();
  matrix.reverseInPlace();

  return matrix;
}

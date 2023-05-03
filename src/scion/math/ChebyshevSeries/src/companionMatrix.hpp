Matrix< Y > companionMatrix( const Y& a ) const {

  // Reference:
  // John P. Boyd
  // Computing the zeros, maxima and inflection points of Chebyshev, Legendre
  // and Fourier series: solving transcendental equations by spectral
  // interpolation and polynomial rootfinding
  // Journal of Engineering Mathematics volume 56, pages 203–219 (2006)
  // doi: 10.1007/s10665-006-9087-5

  // remark: the companion matrix used by numpy is equal to diag * matrix * diag
  // where matrix is the matrix calculated in this function and diag is a
  // diagonal matrix where the i-th element on the diagonal is equal to 1 for
  // i = 0 and equal to sqrt( 1 / 2 ) for all other i.

  // This does not check for order 0: this case is explicitly handled in the
  // roots( ... ) method.

  const unsigned int order = this->order();
  const Y scale = this->coefficients().back() * Y( 2 );

  Matrix< X > matrix( order, order );
  matrix.setZero();

  matrix( order - 1, 0 ) = - ( this->coefficients()[0] - a ) / scale;
  matrix( 0, 1 ) = Y( 1. );
  for ( unsigned int i = 1; i < order - 1; ++i ) {

    matrix( i, i - 1 ) = Y( 0.5 );
    matrix( i, i + 1 ) = Y( 0.5 );
    matrix( order - 1, i ) = - this->coefficients()[i] / scale;
  }
  matrix( order - 1, order - 2 ) += Y( 0.5 );
  matrix( order - 1, order - 1 ) = - this->coefficients()[order - 1] / scale;

  return matrix;
}

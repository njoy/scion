/**
 *  @brief Return the coefficients for a product
 *
 *  Chebyshev polynomials satisfy the following relation:
 *    T(n,x) T(m,x) = ( T(n+m,x) + T(abs(n-m),x) ) / 2 for n,m > 0
 */
std::vector< Y > calculateProduct( const std::vector< Y >& right ) const {

  //! @todo this migth be reimplemented using a cartesian product

  std::vector< Y > coefficients( this->order() + right.size() );
  Y half( 0.5 );
  for ( unsigned int i = 0; i < this->coefficients().size(); ++i ) {

    for ( unsigned int j = 0; j < right.size(); ++j ) {

      auto product = half * this->coefficients()[i] * right[j];
      coefficients[ i + j ] += product;
      coefficients[ j > i ? j - i : i - j ] += product;
    }
  }
  return coefficients;
}

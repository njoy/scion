/**
 *  @brief Return the coefficients for a product
 */
std::vector< Y > calculateProduct( const std::vector< Y >& right ) const {

  //! @todo this migth be reimplemented using a cartesian product

  std::vector< Y > coefficients( this->order() + right.size() );
  for ( unsigned int i = 0; i < this->coefficients().size(); ++i ) {

    for ( unsigned int j = 0; j < right.size(); ++j ) {

      coefficients[ i + j ] += this->coefficients()[i] * right[j];
    }
  }
  return coefficients;
}

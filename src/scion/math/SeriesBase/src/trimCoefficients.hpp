void trimCoefficients() {

  // this removes trailing zeros in the coefficients
  // if all coefficients are zero, it leaves a single order 0 coefficient
  // equal to zero

  if ( Y( 0. ) == this->coefficients().back() ) {

    const auto iter =
    std::find_if( this->coefficients().rbegin(), this->coefficients().rend(),
                  [] ( auto&& coefficient ) { return coefficient != Y( 0. ); } );
    this->coefficients_.erase( iter.base(), this->coefficients_.end() );
    if ( this->coefficients_.size() == 0 ) {

      this->coefficients_.push_back( Y( 0. ) );
    }
  }
}

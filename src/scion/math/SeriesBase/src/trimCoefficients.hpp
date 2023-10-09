void trimCoefficients() {

  // this removes trailing zeros in the coefficients

  if ( 0.0 == this->coefficients().back() ) {

    const auto iter =
    std::find_if( this->coefficients().rbegin(), this->coefficients().rend(),
                  [] ( auto&& coefficient ) { return coefficient != 0.; } );
    this->coefficients_.erase( iter.base(), this->coefficients_.end() );
  }
}

/**
 *  @brief Calculate the mean (first order raw moment) of the series over its domain
 */
auto calculateMean() const {

  if ( this->order() == 0 ) {

    return 0.;
  }
  else {

    // x T(0,x) = T(1,x)
    // x T(m,x) = ( T(m+1,x) + T(m-1,x) ) / 2 for m > 0
    // integral of T(n,x) between -1 and 1 is ( -1^n + 1 ) / ( 1 - n^2 ) for even n
    // integral of T(n,x) between -1 and 1 is 0 for odd n
    auto result = 2. * this->coefficients()[1] / 3.;
    for ( unsigned int i = 3; i < this->coefficients().size(); i += 2 ) {

      auto a = i + 1;
      auto b = i - 1;
      result += this->coefficients()[i] * ( 1. / ( 1. - a * a ) + 1. / ( 1. - b * b ) );
    }
    return result;
  }
}

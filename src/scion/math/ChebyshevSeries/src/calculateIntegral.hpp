/**
 *  @brief Calculate the integral (zeroth order moment) of the series over its domain
 */
auto calculateIntegral() const {

  // integral of T(n,x) between -1 and 1 is ( -1^n + 1 ) / ( 1 - n^2 ) for even n
  // integral of T(n,x) between -1 and 1 is 0 for odd n

  auto result = 2. * this->coefficients().front();
  for ( unsigned int i = 2; i < this->coefficients().size(); i += 2 ) {

    result += 2. * this->coefficients()[i] / ( 1. - i * i );
  }
  return result;

}

/**
 *  @brief Calculate the integral (zeroth order moment) of the series over its domain
 */
auto calculateIntegral() const {

  return X( 2. ) * this->coefficients().front();
}

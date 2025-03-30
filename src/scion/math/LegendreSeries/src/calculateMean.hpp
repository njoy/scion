/**
 *  @brief Calculate the mean (first order raw moment) of the series over its domain
 */
auto calculateMean() const {

  return this->order() == 0
         ? 0.
         : 2. * this->coefficients()[1] / 3.;
}

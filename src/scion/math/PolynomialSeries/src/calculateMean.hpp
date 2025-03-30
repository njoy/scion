/**
 *  @brief Calculate the mean (first order raw moment) of the series over its domain
 */
auto calculateMean() const {

  if ( std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

    auto lower = std::get< IntervalDomain< X > >( this->domain() ).lowerLimit();
    auto upper = std::get< IntervalDomain< X > >( this->domain() ).upperLimit();

    auto coefficients = this->coefficients();
    coefficients.insert( coefficients.begin(), 0. );
    return PolynomialSeries( this->domain(), std::move( coefficients ) ).primitive( lower )( upper );
  }
  else {

    Log::error( "Cannot calculate the integral of a polynomial series with an open domain" );
    throw std::exception();
  }
}

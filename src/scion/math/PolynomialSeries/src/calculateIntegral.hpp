/**
 *  @brief Calculate the integral (zeroth order moment) of the series over its domain
 */
auto calculateIntegral() const {

  if ( std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

    auto lower = std::get< IntervalDomain< X > >( this->domain() ).lowerLimit();
    auto upper = std::get< IntervalDomain< X > >( this->domain() ).upperLimit();
    return this->primitive( lower )( upper );
  }
  else {

    Log::error( "Cannot calculate the integral of a polynomial series with an open domain" );
    throw std::exception();
  }
}

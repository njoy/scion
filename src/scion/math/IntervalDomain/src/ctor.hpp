/**
 *  @brief Constructor
 *
 *  @param lower   the lower limit of the domain
 *  @param upper   the upper limit of the domain
 */
IntervalDomain( X lower, X upper ) :
  lower_( std::move( lower ) ), upper_( std::move( upper ) ) {

  verifyDomain( this->lowerLimit(), this->upperLimit() );
}

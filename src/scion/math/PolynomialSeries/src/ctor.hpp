/**
 *  @brief Constructor
 *
 *  @param domain         the domain of the polynomial series
 *  @param coefficients   the coefficients of the polynomial series function
 *                        (from lowest to highest order coefficient)
 */
PolynomialSeries( DomainVariant domain, std::vector< Y > coefficients ) :
  Parent( std::move( domain ) ),
  coefficients_( std::move( coefficients ) ) {

  verifyCoefficients( this->coefficients() );
}

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series function (from
 *                        lowest to highest order coefficient)
 */
PolynomialSeries( std::vector< Y > coefficients ) :
  PolynomialSeries( OpenDomain< X >(), std::move( coefficients ) ) {}

/**
 *  @brief Constructor
 *
 *  @param lower          the lower limit of the domain
 *  @param upper          the upper limit of the domain
 *  @param coefficients   the coefficients of the Legendre series function (from
 *                        lowest to highest order coefficient)
 */
PolynomialSeries( X lower, X upper, std::vector< Y > coefficients ) :
  PolynomialSeries( IntervalDomain< X >( std::move( lower ), std::move( upper ) ),
                    std::move( coefficients ) ) {}

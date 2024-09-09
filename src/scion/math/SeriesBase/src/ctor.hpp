/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SeriesBase() = default;

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the series (from lowest to highest
 *                        order coefficient)
 *  @param domain         the domain of the series
 */
SeriesBase( DomainVariant domain, std::vector< Y > coefficients ) :
  Parent( std::move( domain ) ),
  coefficients_( std::move( coefficients ) ) {

  verifyCoefficients( this->coefficients() );
}

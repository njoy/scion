//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
SeriesBase() = default;
#endif

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

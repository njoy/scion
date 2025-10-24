/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SeriesBase() = default;

SeriesBase( const SeriesBase& ) = default;
SeriesBase( SeriesBase&& ) = default;

SeriesBase& operator=( const SeriesBase& ) = default;
SeriesBase& operator=( SeriesBase&& ) = default;

/**
 *  @brief Assignment operator
 *
 *  @param coefficient   the zero order coefficient
 */
Derived& operator=( const Y& value ) {

  this->coefficients_ = { value };
  return *static_cast< Derived* >( this );;
}

/**
 *  @brief Constructor
 *
 *  There must be at least 1 coefficient. Trailing zeros in the coefficients are
 *  removed (if all are zero, a single zero coefficient will remain).
 *
 *  @param coefficients   the coefficients of the series (from lowest to highest
 *                        order coefficient)
 *  @param domain         the domain of the series
 */
SeriesBase( DomainVariant domain, std::vector< Y > coefficients ) :
  Parent( std::move( domain ) ),
  coefficients_( std::move( coefficients ) ) {

  verifyCoefficients( this->coefficients() );
  this->trimCoefficients();
}

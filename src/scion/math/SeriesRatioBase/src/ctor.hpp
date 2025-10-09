/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SeriesRatioBase() = default;

SeriesRatioBase( const SeriesRatioBase& ) = default;
SeriesRatioBase( SeriesRatioBase&& ) = default;

SeriesRatioBase& operator=( const SeriesRatioBase& ) = default;
SeriesRatioBase& operator=( SeriesRatioBase&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param numerator     the numerator series
 *  @param denominator   the denominator series
 */
SeriesRatioBase( Series numerator, Series denominator ) :
  Parent( numerator.domain() ),
  numerator_( std::move( numerator ) ),
  denominator_( std::move( denominator ) ) {}

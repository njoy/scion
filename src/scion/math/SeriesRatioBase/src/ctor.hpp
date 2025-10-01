/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SeriesRatioBase() = default;

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

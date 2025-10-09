private:

/**
 *  @brief Private constructor
 */
PolynomialSeriesRatio( Parent series ) : Parent( std::move( series ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
PolynomialSeriesRatio() = default;

PolynomialSeriesRatio( const PolynomialSeriesRatio& ) = default;
PolynomialSeriesRatio( PolynomialSeriesRatio&& ) = default;

PolynomialSeriesRatio& operator=( const PolynomialSeriesRatio& ) = default;
PolynomialSeriesRatio& operator=( PolynomialSeriesRatio&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param numerator     the numerator series
 *  @param denominator   the denominator series
 */
PolynomialSeriesRatio( PolynomialSeries< X, Y > numerator,
                       PolynomialSeries< X, Y > denominator ) :
  Parent( std::move( numerator ), std::move( denominator ) ) {}

/**
 *  @brief Constructor (for an open domain on the polynomial series)
 *
 *  @param numerator     the coefficients of the numerator series
 *                       (from lowest to highest order coefficient)
 *  @param denominator   the coefficients of the denominator series
 *                       (from lowest to highest order coefficient)
 */
PolynomialSeriesRatio( std::vector< Y > numerator,
                       std::vector< Y > denominator ) :
  PolynomialSeriesRatio( PolynomialSeries< X, Y >( std::move( numerator ) ),
                         PolynomialSeries< X, Y >( std::move( denominator ) ) ) {}

/**
 *  @brief Constructor (for an interval domain on the polynomial series)
 *
 *  @param lower         the lower limit of the domain
 *  @param upper         the upper limit of the domain
 *  @param numerator     the coefficients of the numerator series
 *                       (from lowest to highest order coefficient)
 *  @param denominator   the coefficients of the denominator series
 *                       (from lowest to highest order coefficient)
 */
PolynomialSeriesRatio( X lower, X upper,
                       std::vector< Y > numerator,
                       std::vector< Y > denominator ) :
  PolynomialSeriesRatio( PolynomialSeries< X, Y >( lower, upper, std::move( numerator ) ),
                         PolynomialSeries< X, Y >( lower, upper, std::move( denominator ) ) ) {}

/**
 *  @brief Constructor (for an open domain on the polynomial series)
 *
 *  @param numerator     the coefficients of the numerator series
 *                       (from lowest to highest order coefficient)
 */
PolynomialSeriesRatio( std::vector< Y > numerator ) :
  PolynomialSeriesRatio( PolynomialSeries< X, Y >( std::move( numerator ) ),
                         PolynomialSeries< X, Y >( { Y( 1. ) } ) ) {}

/**
 *  @brief Constructor (for an interval domain on the polynomial series)
 *
 *  @param lower         the lower limit of the domain
 *  @param upper         the upper limit of the domain
 *  @param numerator     the coefficients of the numerator series
 *                       (from lowest to highest order coefficient)
 */
PolynomialSeriesRatio( X lower, X upper,
                       std::vector< Y > numerator ) :
  PolynomialSeriesRatio( PolynomialSeries< X, Y >( lower, upper, std::move( numerator ) ),
                         PolynomialSeries< X, Y >( lower, upper, { Y( 1. ) } ) ) {}

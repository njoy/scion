private:

/**
 *  @brief Private constructor
 */
LegendreSeries( Parent series ) : Parent( std::move( series ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
LegendreSeries() = default;

LegendreSeries( const LegendreSeries& ) = default;
LegendreSeries( LegendreSeries&& ) = default;

LegendreSeries& operator=( const LegendreSeries& ) = default;
LegendreSeries& operator=( LegendreSeries&& ) = default;

/**
 *  @brief Assignment operator
 *
 *  @param coefficient   the zero order coefficient
 */
LegendreSeries& operator=( const Y& value ) {

  return Parent::operator=( value );
}

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series (from
 *                        lowest to highest order coefficient)
 */
LegendreSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

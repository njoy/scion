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

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series (from
 *                        lowest to highest order coefficient)
 */
LegendreSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

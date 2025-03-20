private:

/**
 *  @brief Private constructor
 */
ChebyshevSeries( Parent series ) : Parent( std::move( series ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ChebyshevSeries() = default;

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Chebyshev series (from
 *                        lowest to highest order coefficient)
 */
ChebyshevSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

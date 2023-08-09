/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Chebyshev series (from
 *                        lowest to highest order coefficient)
 */
ChebyshevSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}
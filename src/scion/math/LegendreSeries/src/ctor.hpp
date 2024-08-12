//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
LegendreSeries() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Legendre series (from
 *                        lowest to highest order coefficient)
 */
LegendreSeries( std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

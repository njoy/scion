//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
PolynomialSeries() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param domain         the domain of the polynomial series
 *  @param coefficients   the coefficients of the polynomial series
 *                        (from lowest to highest order coefficient)
 */
PolynomialSeries( DomainVariant domain, std::vector< Y > coefficients ) :
  Parent( IntervalDomain( -1., 1. ), std::move( coefficients ) ) {}

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the polynomial series (from
 *                        lowest to highest order coefficient)
 */
PolynomialSeries( std::vector< Y > coefficients ) :
  PolynomialSeries( OpenDomain< X >(), std::move( coefficients ) ) {}

/**
 *  @brief Constructor
 *
 *  @param lower          the lower limit of the domain
 *  @param upper          the upper limit of the domain
 *  @param coefficients   the coefficients of the polynomial series (from
 *                        lowest to highest order coefficient)
 */
PolynomialSeries( X lower, X upper, std::vector< Y > coefficients ) :
  PolynomialSeries( IntervalDomain< X >( std::move( lower ), std::move( upper ) ),
                    std::move( coefficients ) ) {}

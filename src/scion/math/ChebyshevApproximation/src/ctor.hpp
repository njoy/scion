//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
ChebyshevApproximation() = default;
#endif

/**
 *  @brief Constructor
 *
 *  @param domain      the domain of the approximated function
 *  @param series      the Chebyshev series that approximates the function
 */
ChebyshevApproximation( IntervalDomain< X > domain,
                        ChebyshevSeries< X, Y > series ) :
  Parent( std::move( domain ) ),
  lower_( domain.lowerLimit() ), upper_( domain.upperLimit() ),
  series_( std::move( series ) ) {}

/**
 *  @brief Constructor
 *
 *  @param lower           the lower limit of the domain
 *  @param upper           the upper limit of the domain
 *  @param coefficients    the coefficients that approximate the function
 */
ChebyshevApproximation( X lower, X upper, std::vector< Y > coefficients ) :
  ChebyshevApproximation( IntervalDomain( lower, upper ),
                          ChebyshevSeries< X, Y >( std::move( coefficients ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param lower       the lower limit of the domain
 *  @param upper       the upper limit of the domain
 *  @param function    the function to be approximated
 *  @param order       the order of the approximation
 */
template < typename Functor >
ChebyshevApproximation( X lower, X upper, Functor&& function, unsigned int order ) :
  ChebyshevApproximation(
      lower, upper,
      calculateCoefficients( lower, upper,
                             std::forward< Functor >( function ), order ) ) {}

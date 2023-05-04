/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Chebyshev series (from
 *                        lowest to highest order coefficient)
 */
ChebyshevApproximation( X lower, X upper, ChebyshevSeries< X, Y > series ) :
  Parent( IntervalDomain( lower, upper ) ),
  lower_( lower ), upper_( upper ),
  series_( std::move( series ) ) {}

/**
 *  @brief Constructor
 *
 *  @param coefficients   the coefficients of the Chebyshev series (from
 *                        lowest to highest order coefficient)
 */
template < typename Functor >
ChebyshevApproximation( X lower, X upper, Functor&& function, unsigned int order ) :
  ChebyshevApproximation(
      lower, upper,
      ChebyshevSeries< X, Y >(
          calculateCoefficients( lower, upper,
                                 std::forward< Functor >( function ),
                                 order ) ) ) {}

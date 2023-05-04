/**
 *  @brief Constructor
 *
 *  @param lower       the lower limit of the domain
 *  @param upper       the upper limit of the domain
 *  @param series      the Chebyshev series that approximates the function
 */
ChebyshevApproximation( X lower, X upper, ChebyshevSeries< X, Y > series ) :
  Parent( IntervalDomain( lower, upper ) ),
  lower_( lower ), upper_( upper ),
  series_( std::move( series ) ) {}

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
      ChebyshevSeries< X, Y >(
          calculateCoefficients( lower, upper,
                                 std::forward< Functor >( function ),
                                 order ) ) ) {}

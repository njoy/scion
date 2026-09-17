/**
 *  @brief Constructor
 *
 *  @param first        the first derivative of the function
 *  @param second       the second derivative of the function
 *  @param iterations   the maximum number of iterations
 */
AbsoluteErrorSplit( FirstDerivative first,
                    SecondDerivative second,
                    int iterations = 20 ) :
  first_( std::move( first ) ),
  second_( std::move( second ) ),
  iterations_( iterations ) {}

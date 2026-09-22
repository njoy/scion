/**
 *  @brief Constructor
 *
 *  @param function     the function
 *  @param first        the first derivative
 *  @param second       the second derivative
 *  @param iterations   the number of iterations (default is 20)
 */
RelativeErrorSplit( Function function,
                    FirstDerivative first,
                    SecondDerivative second,
                    int iterations = 20 ) :
  function_( std::move( function ) ),
  first_( std::move( first ) ),
  second_( std::move( second ) ),
  iterations_( iterations ) {}

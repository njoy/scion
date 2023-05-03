/**
 *  @brief Return the derivative of the Chebyshev series
 *
 *  The derivative function of a Chebyshev series function is another
 *  Chebyshev series function.
 *
 *  The derivative function is defined over the same domain as the
 *  original function.
 */
ChebyshevSeries derivative() const {

  const unsigned int order = this->order();
  if ( 0 == order ) {

    return ChebyshevSeries( { Y( 0. ) } );
  }
  else {

    throw std::exception();
  }
}

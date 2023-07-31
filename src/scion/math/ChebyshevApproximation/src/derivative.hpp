/**
 *  @brief Return the derivative of the approximated function
 *
 *  The derivative function of an approximated function is another approximated
 *  function. The derivative is equal to the derivative of the underlying
 *  Chebyshev series and is defined over the same domain as the original
 *  approximated function.
 */
ChebyshevApproximation derivative() const {

  return ChebyshevApproximation( IntervalDomain( this->lower_, this->upper_ ),
                                 this->series_.derivative() );
}

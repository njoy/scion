/**
 *  @brief Return the primitive (or antiderivative) of the approximated function
 *
 *  The primitive of an approximated function is another approximated
 *  function. The primitive is equal to the primitive of the underlying
 *  Chebyshev series and is defined over the same domain as the original
 *  approximated function.
 *
 *  The integral function is defined so that the integral function for x = left
 *  equals 0.
 *
 *  @param[in] left    the left bound of the integral (default = 0)
 */
ChebyshevApproximation primitive( const X& left = X( 0. ) ) const {

  return ChebyshevApproximation( IntervalDomain( this->lower_, this->upper_ ),
                                 this->series_.primitive( left ) );
}

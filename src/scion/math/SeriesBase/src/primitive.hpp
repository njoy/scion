/**
 *  @brief Return the primitive (or antiderivative) of the series
 *
 *  @param[in] left    the left bound of the integral (default = 0)
 */
Derived primitive( const X& left = X( 0. ) ) const {

  return static_cast< const Derived* >( this )->calculatePrimitive( left );
}

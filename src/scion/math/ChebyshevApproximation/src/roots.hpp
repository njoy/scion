/**
 *  @brief Calculate the real roots of the approximated function so that f(x) = a
 *
 *  This function calculates all roots on the real axis of the approximated
 *  function as the roots of the underlying Chebyshev series.
 *
 *  @param[in] a   the value of a (default is zero)
 */
std::vector< X > roots( const Y& a = Y( 0. ) ) const {

  return this->series_.roots( a );
}

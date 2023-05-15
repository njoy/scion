/**
 *  @brief Calculate the real roots of the Chebyshev series so that f(x) = a
 *
 *  This function calculates all roots on the real axis of the Chebyshev series.
 *
 *  The roots of the Chebyshev series are the eigenvalues of the Frobenius
 *  companion matrix whose elements are trivial functions of the coefficients of
 *  the Chebyshev series. The resulting roots are in the complex plane so the
 *  roots that are not on the real axis are filtered out. The roots on the real
 *  axis are then improved upon using a few iterations of the Newton-Rhapson
 *  method.
 *
 *  @param[in] a   the value of a (default is zero)
 */
std::vector< X > roots( const Y& a = Y( 0. ) ) const {

  std::vector< X > roots;
  roots.reserve( this->order() );

  if ( 1 == this->order() ) {

    roots.emplace_back( - ( this->coefficients()[0] - a ) / this->coefficients()[1] );
  }
  else if ( 1 < this->order() ) {

    Eigen::EigenSolver< Matrix< Y > > solver( this->companionMatrixNumpy( a ), false );
    ChebyshevSeries derivative = this->derivative();
    auto functor = [&a, this] ( const X& x ) { return this->evaluate( x ) - a; };

    for ( const auto& value : solver.eigenvalues().reshaped() ) {

      if ( isCloseToZero( value.imag() ) ) {

        roots.emplace_back( value.real() );
      }
    }

    std::sort( roots.begin(), roots.end() );
    roots.erase( std::unique( roots.begin(), roots.end() ), roots.end() );
  }

  return roots;
}

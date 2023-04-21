/**
 *  @brief Calculate the roots of the Legendre series so that f(x) = a
 *
 *  This function calculates all roots in the complex plane of the polynomial
 *  series. The roots of the polynomial series are the eigenvalues of the
 *  Frobenius companion matrix whose elements are trivial functions of the
 *  coefficients of the polynomial series. The roots on the real axis are then
 *  improved upon using a few iterations of the Newton-Rhapson method.
 *
 *  @param[in] a   the value of a (default is zero)
 */
std::vector< std::complex< X > > roots( const Y& a = Y( 0. ) ) const {

  std::vector< std::complex< X > > roots;
  roots.reserve( this->order() );

  if ( 1 == this->order() ) {

    roots.emplace_back( - ( this->coefficients()[0] - a ) / this->coefficients()[1] );
  }
  else if ( 1 < this->order() ) {

    Eigen::EigenSolver< Matrix< Y > > solver( this->companionMatrix( a ), false );

    LegendreSeries derivative = this->derivative();
    auto functor = [&a, this] ( const X& x ) { return this->evaluate( x ) - a; };

    for ( const auto& value : solver.eigenvalues().reshaped() ) {

      if ( isCloseToZero( value.imag() ) ) {

        roots.emplace_back( newton( value.real(), functor, derivative ) );
      }
      else {

        roots.emplace_back( value );
      }
    }
  }

  return roots;
}

/**
 *  @brief Calculate the real roots of the series so that f(x) = a
 *
 *  This function calculates all roots on the real axis of the series.
 *
 *  The roots of the series are the eigenvalues of the companion matrix whose
 *  elements are trivial functions of the coefficients of the series. The
 *  resulting roots are in the complex plane so the roots that are not on the
 *  real axis are filtered out.
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

    Eigen::EigenSolver< Matrix< Y > >
    solver( static_cast< const Derived* >( this )->companionMatrix( a ), false );

    Derived derivative = this->derivative();
    auto functor = [&a, this] ( const X& x ) { return ( *this )( x ) - a; };

    for ( const auto& value : solver.eigenvalues() ) {

      if ( isCloseToZero( value.imag() ) ) {

        roots.emplace_back( derivative( value.real() ) != X( 0. )
                            ? newton( value.real(), functor, derivative )
                            : value.real() );
      }
    }

    std::sort( roots.begin(), roots.end() );
    roots.erase( std::unique( roots.begin(), roots.end() ), roots.end() );
  }

  return roots;
}

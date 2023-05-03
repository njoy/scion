/**
 *  @brief Linearise the Chebyshev series and return a LinearLinearTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

  if ( 0 == this->order() ) {

    return LinearLinearTable< X, Y >( { -1., +1. },
                                      { this->coefficients().front(),
                                        this->coefficients().front() } );
  }
  else if ( 1 == this->order() ) {

    const auto a = this->coefficients().back();
    const auto b = this->coefficients().front();
    return LinearLinearTable< X, Y >( { -1., +1. }, { b - a, b + a } );
  }
  else {

    //! @todo implement ths
    throw std::exception();
  }
}

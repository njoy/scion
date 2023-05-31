/**
 *  @brief Linearise the approximated function and return an InterpolationTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
InterpolationTable< X, Y >
linearise( Convergence&& convergence = Convergence() ) const {

  if ( 0 == this->order() ) {

    return InterpolationTable< X, Y >( { this->invert( -1. ),
                                         this->invert( +1. ) },
                                       { this->coefficients().front(),
                                         this->coefficients().front() } );
  }
  else if ( 1 == this->order() ) {

    const auto a = this->coefficients().back();
    const auto b = this->coefficients().front();
    return InterpolationTable< X, Y >( { this->invert( -1. ),
                                         this->invert( +1. ) },
                                       { b - a, b + a } );
  }
  else {

    // linearise the Chebyshev series
    auto linearised = this->series_.linearise( convergence );

    // transform the x values
    std::vector< X > x( linearised.numberPoints() );
    std::transform( linearised.x().cbegin(), linearised.x().cend(), x.begin(),
                    [this] ( const auto& value ) { return this->invert( value ); } );

    return InterpolationTable< X, Y >( std::move( x ),
                                       linearised.y() );
  }
}

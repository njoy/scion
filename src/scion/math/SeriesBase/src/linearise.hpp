/**
 *  @brief Linearise the series and return a LinearLinearTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

  if ( ! std::holds_alternative< IntervalDomain< X > >( this->domain() ) ) {

    Log::error( "Cannot linearise the series because it does not have an "
                "interval domain" );
    throw std::exception();
  }

  const auto domain = std::get< IntervalDomain< X > >( this->domain() );

  if ( 0 == this->order() ) {

    return LinearLinearTable< X, Y >( { domain.lowerLimit(), domain.upperLimit() },
                                      { this->coefficients().front(),
                                        this->coefficients().front() } );
  }
  else if ( 1 == this->order() ) {

    const auto a = this->coefficients().back();
    const auto b = this->coefficients().front();
    return LinearLinearTable< X, Y >( { domain.lowerLimit(), domain.upperLimit() },
                                      { a * domain.lowerLimit() + b,
                                        a * domain.upperLimit() + b } );
  }
  else {

    std::vector< X > x;
    std::vector< Y > y;
    linearisation::Lineariser lineariser( x, y );
    lineariser( linearisation::grid( *this, domain.lowerLimit(), domain.upperLimit() ),
                *this,
                std::forward< Convergence >( convergence ),
                linearisation::MidpointSplit< X >() );

    return LinearLinearTable< X, Y >( std::move( x ), std::move( y ) );
  }
}

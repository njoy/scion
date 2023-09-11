/**
 *  @brief Linearise the table and return a LinearLinearTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

  std::vector< X > x = { this->x().front() };
  std::vector< Y > y = { this->y().front() };
  for ( unsigned int i = 1; i < this->x().size(); ++i ) {

    x.push_back( this->x()[i] );
    x.push_back( this->x()[i] );
    y.push_back( this->y()[i-1] );
    y.push_back( this->y()[i] );
  }
  x.pop_back();
  y.pop_back();

  return LinearLinearTable< X, Y >( std::move( x ), std::move( y ) );
}

/**
 *  @brief Linearise the table and return a LinearLinearTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

  std::vector< X > x;
  std::vector< Y > y;
  linearisation::Lineariser lineariser( x, y );
  lineariser( this->x(),
              *this,
              std::forward< Convergence >( convergence ),
              linearisation::MidpointSplit< X >() );

  return LinearLinearTable< X, Y >( std::move( x ), std::move( y ) );
}

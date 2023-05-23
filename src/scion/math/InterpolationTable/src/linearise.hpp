/**
 *  @brief Linearise the table and return a LinearLinearTable
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

  auto linearise = [&convergence] ( const auto& table )
                                  { return table.linearise( convergence ); };

  if ( this->numberRegions() > 1 ) {

    std::vector< X > x;
    std::vector< Y > y;

    auto check = [this] ( const auto& table ) {

      if ( table.x().end() != this->x().end() ) {
        if ( *( table.x().end() ) == table.x().back() ) {
          if ( *( table.y().end() ) != table.y().back() ) {
            return true;
          }
        }
        return false;
      }
      return true;
    };

    for ( const auto& table : this->tables_ ) {

      auto linearised = std::visit( linearise, table );
      bool isJump = std::visit( check, table );

      x.insert( x.end(),
                linearised.x().begin(),
                isJump ? linearised.x().end() : std::prev( linearised.x().end() ) );
      y.insert( y.end(),
                linearised.y().begin(),
                isJump ? linearised.y().end() : std::prev( linearised.y().end() ) );
    }

    return LinearLinearTable< X, Y >( std::move( x ), std::move( y ) );
  }
  else {

    return std::visit( linearise, this->tables_.front() );
  }
}

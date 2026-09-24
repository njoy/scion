/**
 *  @brief Linearise the table and return a new InterpolationTable
 *
 *  This always stitches the tabulated data of each region back together and reconstructs
 *  a new table, even for a linearised table (it can still contain a discontinuity of more
 *  than 2 points). Since the underlying views ensure unique x grids in each view, stitching
 *  the table back together will remove the extraneous points.
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
InterpolationTable linearise( Convergence&& convergence = Convergence() ) const {

  std::vector< X > x;
  std::vector< Y > y;
  std::vector< std::size_t > boundaries;
  std::vector< interpolation::InterpolationType > interpolants;

  auto linearise = [&convergence] ( const auto& table )
                                  { return table.linearise( convergence ); };

  auto check = [this] ( const auto& table ) {

    return table.x().end() != this->x().end()
           ? ( *( table.x().end() ) == table.x().back() )
             ? ( *( table.y().end() ) != table.y().back() ? true : false )
             : false
           : true;
  };

  for ( const auto& table : this->tables_ ) {

    auto linearised = std::visit( linearise, table );
    bool isJumpOrEnd = std::visit( check, table );

    if ( isJumpOrEnd ) {

      x.insert( x.end(), linearised.first.begin(), linearised.first.end() );
      y.insert( y.end(), linearised.second.begin(), linearised.second.end() );
      boundaries.push_back( x.size() - 1 );
      interpolants.push_back( interpolation::InterpolationType::LinearLinear );
    }
    else {

      x.insert( x.end(), linearised.first.begin(), std::prev( linearised.first.end() ) );
      y.insert( y.end(), linearised.second.begin(), std::prev( linearised.second.end() ) );
    }
  }

  return InterpolationTable( std::move( x ), std::move( y ),
                             std::move( boundaries ), std::move( interpolants ) );
}

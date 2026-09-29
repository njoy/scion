/**
 *  @brief Linearise the table and return a new InterpolationTable
 *
 *  If the table is already linearised and curated, a copy of the table is returned.
 *  Otherwise, the tabulated data of each region is stitched back together and a new table
 *  is reconstructed. Since the underlying views ensure unique x grids in each view,
 *  stitching the table back together will remove the extraneous points.
 *
 *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
 */
template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
InterpolationTable linearise( Convergence&& convergence = Convergence() ) const {

  if ( ! ( this->isLinearised() && this->isCurated() ) ) {

    std::vector< X > x;
    std::vector< Y > y;
    std::vector< std::size_t > boundaries;
    std::vector< interpolation::InterpolationType > interpolants;

    auto linearise = [&convergence] ( const auto& table )
                                    { return table.linearise( convergence ); };

    auto check = [this] ( const auto& table ) {

      if ( table.x().end() == this->x().end() ) {

        // end of table
        return true;
      }
      else if ( *( table.x().end() ) != table.x().back() ) {

        // no jump
        return false;
      }
      else {

        // this is a jump: move to the last point
        auto xNext = std::prev( std::upper_bound( table.x().end(), this->x().end(),
                                                  table.x().back() ) );
        auto yNext = std::next( table.y().end(), std::distance( table.x().end(), xNext ) );
        return *yNext != table.y().back();
      }
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
  else {

    return *this;
  }
}

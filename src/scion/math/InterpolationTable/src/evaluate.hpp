/**
 *  @brief Evaluate the function for a value of x
 *
 *  @param x   the value to be evaluated
 */
Y evaluate( const X& x ) const {

  std::size_t index = 0;

  if ( this->numberRegions() > 1 ) {

    // look in the grid for the x value
    // upper_bound is used to get above jumps in the grid
    auto xIter = std::upper_bound( this->x().begin(),
                                   this->x().end(), x );
    index = std::distance( this->x().begin(), xIter );

    // get the table that has to interpolate on this value
    auto bIter = std::lower_bound( this->boundaries().begin(),
                                   this->boundaries().end(), index );
    if ( this->boundaries().end() == bIter ) {

      --bIter;
    }
    index = std::distance( this->boundaries().begin(), bIter );
  }

  return std::visit( [&x] ( const auto& table )
                          { return table.evaluate( x ); },
                     this->tables()[index] );
}

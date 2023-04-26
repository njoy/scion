std::vector< X > grid() const {

  std::vector< X > grid = { X( -1. ), X( 1. ) };

  // add roots of the first derivative
  const LegendreSeries first = this->derivative();
  std::vector< X > temp = first.roots();
  grid.insert( grid.end(), temp.begin(), temp.end() );

  // add roots of the second derivative
  temp = first.derivative().roots();
  grid.insert( grid.end(), temp.begin(), temp.end() );

  // sort the grid and remove duplicates
  std::sort( grid.begin(), grid.end() );
  grid.erase( std::unique( grid.begin(), grid.end() ), grid.end() );

  // remove everything outside of the domain
  grid.erase( std::lower_bound( grid.begin(), grid.end(), X( -1. ) ), grid.begin() );
  grid.erase( std::next( std::lower_bound( grid.begin(), grid.end(), X( +1. ) ) ), grid.end() );

  //! @todo remove points that are too close to one another

  return grid;
}

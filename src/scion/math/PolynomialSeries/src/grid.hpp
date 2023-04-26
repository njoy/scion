std::vector< X > grid( const X& lowerLimit, const X& upperLimit ) const {

  std::vector< X > grid = { lowerLimit, upperLimit };

  // add roots of the first derivative
  const PolynomialSeries first = this->derivative();
  std::vector< X > temp = first.roots();
  grid.insert( grid.end(), temp.begin(), temp.end() );

  // add roots of the second derivative
  temp = first.derivative().roots();
  grid.insert( grid.end(), temp.begin(), temp.end() );

  // sort the grid and remove duplicates
  std::sort( grid.begin(), grid.end() );
  grid.erase( std::unique( grid.begin(), grid.end() ), grid.end() );

  // remove everything outside of the domain
  grid.erase( std::lower_bound( grid.begin(), grid.end(), lowerLimit ), grid.begin() );
  grid.erase( std::next( std::lower_bound( grid.begin(), grid.end(), upperLimit ) ), grid.end() );

  //! @todo remove points that are too close to one another

  return grid;
}

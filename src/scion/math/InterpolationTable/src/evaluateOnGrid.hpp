std::vector< Y > evaluateOnGrid( const std::vector< X >& x ) const {

  std::vector< Y > y( x.size(), Y( 0. ) );

  auto xIter = std::lower_bound( x.begin(), x.end(), this->x().front() );
  if ( *std::next( xIter ) == this->x().front() ) {

    // move to the next x value in case of a jump
    ++xIter;
  }
  auto yIter = std::next( y.begin(), std::distance( x.begin(), xIter ) );

  auto xTable = this->x().begin();
  auto yTable = this->y().begin();

  for ( ; xIter != x.end(); ++xIter ) {

    if ( *xIter < *xTable ) {

      *yIter = interpolation::linlin( *xIter, *std::prev( xTable ), *xTable,
                                              *std::prev( yTable ), *yTable );
    }
    else {

      *yIter = *yTable;
      ++xTable;
      ++yTable;

      if ( this->x().end() == xTable ) {

        break;
      }
    }
    ++yIter;
  }

  return y;
}

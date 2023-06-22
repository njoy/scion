std::vector< Y > evaluateOnGrid( const std::vector< X >& x ) const {

  std::vector< Y > y( x.size(), Y( 0. ) );

  auto xIter = std::lower_bound( x.begin(), x.end(), this->x().front() );
  auto yIter = std::next( y.begin(), std::distance( x.begin(), xIter ) );

  auto xTable = this->x().begin();
  auto yTable = this->y().begin();

  if ( x.begin() != xIter ) {

    if ( Y( 0. ) != *yTable ) {

      Log::error( "The threshold table's first y value is not zero" );
      Log::info( "Found y = ", *yTable );
      throw std::exception();
    }
  }

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

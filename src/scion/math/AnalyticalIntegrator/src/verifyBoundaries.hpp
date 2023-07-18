static void verifyBoundaries( const std::vector< X >& boundaries ) {

  if ( ! verification::isSorted( boundaries ) ) {

    Log::error( "The integration boundary values do not appear to be sorted" );
    throw std::exception();
  }

  if ( ! verification::isUnique( boundaries ) ) {

    Log::error( "The integration boundary values do not appear to be unique" );

    auto iter = std::adjacent_find( boundaries.begin(), boundaries.end() );
    while ( iter != boundaries.end() ) {

      Log::info( "Duplicate x value found: {}", *iter );
      iter = std::adjacent_find( ++iter, boundaries.end() );
    }
    throw std::exception();
  }
}

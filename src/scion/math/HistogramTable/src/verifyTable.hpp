static void verifyTable( const XContainer& x,
                         const YContainer& ) {

  if ( ! verification::isUnique( x ) ) {

    Log::error( "The x values do not appear to be unique for tabulated values "
                "with histogram or constant interpolation" );

    auto iter = std::adjacent_find( x.begin(), x.end() );
    while ( iter != x.end() ) {

      Log::info( "Duplicate x value found: ", *iter );
      iter = std::adjacent_find( ++iter, x.end() );
    }
    throw std::exception();
  }
}

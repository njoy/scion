static void verifyTable( const XContainer& x,
                         const YContainer& y ) {

  if ( x.end() != std::adjacent_find( x.begin(), x.end() ) ) {

    Log::error( "The x values do not appear to be unique for tabulated values "
                "with lin-log interpolation" );

    auto iter = std::adjacent_find( x.begin(), x.end() );
    while ( iter != x.end() ) {

      Log::info( "Duplicate x value found: ", *iter );
      iter = std::adjacent_find( ++iter, x.end() );
    }
    throw std::exception();
  }
}

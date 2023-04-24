static void verifyTable( const XContainer& x,
                         const YContainer& y ) {

  if ( ( 2 > x.size() ) || ( 2 > y.size() ) ) {

    Log::error( "Insufficient x or y values defined for tabulated data "
                "(at least 2 points are required)" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( x.size() != y.size() ) {

    Log::error( "Inconsistent number of x and y values for tabulated data" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( ! std::is_sorted( x.begin(), x.end() ) ) {

    Log::error( "The x values do not appear to be in ascending order" );
    throw std::exception();
  }
}

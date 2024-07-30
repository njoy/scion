static void verifyTable( const XContainer& x, const FContainer& f ) {

  if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
       ( ! verification::isAtLeastOfSize( f, 2 ) ) ) {

    Log::error( "Insufficient x or f values defined for x,f(y) tabulated data "
                "with a single interpolation type (at least 2 points are "
                "required)" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "f.size(): {}", f.size() );
    throw std::exception();
  }

  if ( ! verification::isSameSize( x, f ) ) {

    Log::error( "Inconsistent number of x and f values for x,f(y) tabulated data "
                "with a single interpolation type" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "f.size(): {}", f.size() );
    throw std::exception();
  }

  if ( ! verification::isSorted( x ) ) {

    Log::error( "The x values do not appear to be in ascending order for "
                "x,f(y) tabulated data with a single interpolation type" );
    throw std::exception();
  }

  if ( ! verification::isUnique( x ) ) {

    Log::error( "The x values do not appear to be unique for x,f(y) tabulated values "
                "with a single interpolation type" );

    auto iter = std::adjacent_find( x.begin(), x.end() );
    while ( iter != x.end() ) {

      Log::info( "Duplicate x value found: {}", *iter );
      iter = std::adjacent_find( ++iter, x.end() );
    }
    throw std::exception();
  }
}

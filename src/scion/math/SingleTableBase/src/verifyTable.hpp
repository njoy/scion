static IntervalDomain< X >
verifyTableAndRetrieveDomain( const XContainer& x, const YContainer& y ) {

  if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
       ( ! verification::isAtLeastOfSize( y, 2 ) ) ) {

    Log::error( "Insufficient x or y values defined for x,y tabulated data "
                "with a single interpolation type (at least 2 points are "
                "required)" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( ! verification::isSameSize( x, y ) ) {

    Log::error( "Inconsistent number of x and y values for x,y tabulated data "
                "with a single interpolation type" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( ! verification::isSorted( x ) ) {

    Log::error( "The x values do not appear to be in ascending order for "
                "x,y tabulated data with a single interpolation type" );
    throw std::exception();
  }

  if ( ! verification::isUnique( x ) ) {

    Log::error( "The x values do not appear to be unique for x,y tabulated values "
                "with a single interpolation type" );

    auto iter = std::adjacent_find( x.begin(), x.end() );
    while ( iter != x.end() ) {

      Log::info( "Duplicate x value found: {}", *iter );
      iter = std::adjacent_find( ++iter, x.end() );
    }
    throw std::exception();
  }

  return IntervalDomain( x.front(), x.back() );
}

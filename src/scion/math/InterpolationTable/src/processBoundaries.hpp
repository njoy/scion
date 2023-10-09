static std::tuple< std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( const std::vector< X >& x, const std::vector< Y >& y,
                   std::vector< std::size_t >&& boundaries,
                   std::vector< interpolation::InterpolationType >&& interpolants  ) {

  if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
       ( ! verification::isAtLeastOfSize( y, 2 ) ) ) {

    Log::error( "Insufficient x or y values defined for tabulated data "
                "(at least 2 points are required)" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( ! verification::isSameSize( x, y ) ) {

    Log::error( "Inconsistent number of x and y values for tabulated data" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "y.size(): {}", y.size() );
    throw std::exception();
  }

  if ( ! verification::isSameSize( boundaries, interpolants ) ) {

    Log::error( "Inconsistent number of boundaries and interpolants for tabulated data" );
    Log::info( "boundaries.size(): {}", boundaries.size() );
    Log::info( "interpolants.size(): {}", interpolants.size() );
    throw std::exception();
  }

  if ( boundaries.back() != x.size() - 1 ) {

    Log::error( "The last boundary value does not point to the last x value" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "boundaries.back(): {}", boundaries.back() );
    throw std::exception();
  }

  if ( ! verification::isSorted( x ) ) {

    Log::error( "The x values do not appear to be in ascending order" );
    throw std::exception();
  }

  auto xIter = std::adjacent_find( x.begin(), x.end() );
  auto bIter = boundaries.begin();
  while ( xIter != x.end() ) {

    auto index = std::distance( x.begin(), xIter );
    bIter = std::lower_bound( bIter, boundaries.end(), index );
    if ( *bIter != index ) {

      auto iIter = std::next( interpolants.begin(),
                              std::distance( boundaries.begin(), bIter ) );
      boundaries.insert( bIter, index );
      interpolants.insert( iIter, *iIter );
    }
    ++xIter;
    if ( std::next( xIter ) == x.end() ) {

      Log::error( "A jump in the x grid cannot occur at the end of the x grid" );
      throw std::exception();
    }
    if ( *std::next( xIter ) == *xIter ) {

      Log::error( "An x value can only be repeated a maximum of two times" );
      Log::info( "x = {} is present at least three times", *xIter );
      throw std::exception();
    }
    xIter = std::adjacent_find( xIter, x.end() );
  }

  return { std::move( boundaries ), std::move( interpolants ) };
}

static std::tuple< std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( const std::vector< X >& x, const std::vector< Y >& y,
                   interpolation::InterpolationType interpolant ) {

  return processBoundaries( x, y,
                            { x.size() > 0 ? x.size() - 1 : 0 },
                            { interpolant } );
}

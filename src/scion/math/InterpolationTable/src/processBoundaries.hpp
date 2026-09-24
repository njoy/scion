/**
 *  @brief Curate the tabulated data
 *
 *  Curation currently consists of removing extraneous interior points in discontinuities
 *  in the data.
 *
 *  The boundaries array is assumed to already have a boundary indices pointing to the first
 *  point of every jump, so this function only has to reduce the boundary values that come
 *  after a curated jump by the number of points that were removed. This is guaranteed by
 *  processBoundaries() prior to calling this function.
 */
static void curateTable( std::vector< X >& x, std::vector< Y >& y,
                         std::vector< std::size_t >& boundaries,
                         std::vector< interpolation::InterpolationType >& /* interpolants */ ) {

  auto xIter = std::adjacent_find( x.begin(), x.end() );
  auto bIter = boundaries.begin();
  while ( xIter != x.end() ) {

    auto xNext = std::upper_bound( xIter, x.end(), *xIter );
    auto number = std::distance( xIter, xNext );

    if ( number > 2 ) {

      Log::warning( "x = {} is present {} times, extraneous points will be removed", *xIter, number );

      std::size_t index = std::distance( x.begin(), xIter );
      auto yIter = std::next( y.begin(), index );
      auto yNext = std::next( yIter, number );

      x.erase( std::next( xIter ), std::prev( xNext ) );
      y.erase( std::next( yIter ), std::prev( yNext ) );

      auto offset = number - 2;
      bIter = std::upper_bound( bIter, boundaries.end(), index );
      std::transform( bIter, boundaries.end(), bIter,
                      [&] ( auto&& boundary ) { return boundary - offset; } );
    }

    xIter = std::adjacent_find( std::next( xIter ), x.end() );
  }
}

/**
 *  @brief Verify and correct boundaries and interpolants
 *
 *  This function does a lot, so here's an overview of what it does. First of all, it verifies
 *  the following things:
 *    - There are at least 2 values in the x and y grid
 *    - The x and y grid have the same size
 *    - The number of boundaries and interpolants are the same
 *    - The last boundary index is equal to the index of the last x value
 *    - The x grid is sorted
 *
 *  Next, this function will look for every jump in the x grid and check if the jump corresponds
 *  to a change in interpolation region (meaning that the index of the first x value in the jump
 *  is in the boundaries). If that is not the case, an additional interpolation region wil be
 *  inserted. This ensures that none of the interpolation regions will contain a jump in their
 *  local x grid.
 *
 *  In some cases, the boundary values can point to the second point of a jump. While this is not
 *  an error (we will never interpolate on a jump), we need the boundaries to point to the first
 *  point in the jump instead of the second one. When this is encountered, the boundary value is
 *  adjusted. This change is made silently as it does not constitute an error on the user side.
 *
 *  A jump at the beginning or end of the x grid is allowed. However, if one of these jumps is
 *  detected, then the first or last point is just removed.
 *
 *  If curate is true, discontinuities of more than 2 points are reduced to the first and last
 *  point of the jump.
 */
static std::tuple< std::vector< X >,
                   std::vector< Y >,
                   std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( std::vector< X >&& x, std::vector< Y >&& y,
                   std::vector< std::size_t >&& boundaries,
                   std::vector< interpolation::InterpolationType >&& interpolants,
                   bool curate = false ) {

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
  auto iIter = interpolants.begin();
  while ( xIter != x.end() ) {

    // determine the next x value
    auto xNext = std::upper_bound( xIter, x.end(), *xIter );
    auto number = std::distance( xIter, xNext );

    // set the boundary for this jump, insert it if necessary
    // index is always positive since xIter is x.begin() or higher iterator
    std::size_t index = std::distance( x.begin(), xIter );
    bIter = std::lower_bound( bIter, boundaries.end(), index );
    if ( *bIter != index ) {

      if ( *bIter < index + number ) {

        *bIter = index;
      }
      else {

        iIter = std::next( interpolants.begin(),
                           std::distance( boundaries.begin(), bIter ) );
        bIter = boundaries.insert( bIter, index );
        iIter = interpolants.insert( iIter, *iIter );
      }
    }

    xIter = std::adjacent_find( xNext, x.end() );
  }

  if ( curate ) {

    curateTable( x, y, boundaries, interpolants );
  }

  // check for a jump at the beginning of the table
  xIter = x.begin();
  if ( *xIter == *( std::next( xIter ) ) ) {

    Log::warning( "A jump at the beginning of the table (x = {}) has been removed", *xIter );
    x.erase( x.begin() );
    y.erase( y.begin() );
    boundaries.erase( boundaries.begin() );
    interpolants.erase( interpolants.begin() );
    std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                    [] ( auto&& boundary ) { return boundary - 1; } );
  }

  // check for a jump at the end of the table
  xIter = std::prev( x.end() );
  if ( *xIter == *( std::prev( xIter ) ) ) {

    Log::warning( "A jump at the end of the table (x = {}) has been removed", *xIter );
    x.erase( std::prev( x.end() ) );
    y.erase( std::prev( y.end() ) );
  }

  return { std::move( x ), std::move( y ),
           std::move( boundaries ), std::move( interpolants ) };
}

static std::tuple< std::vector< X >,
                   std::vector< Y >,
                   std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( std::vector< X >&& x, std::vector< Y >&& y,
                   interpolation::InterpolationType interpolant,
                   bool curate = false ) {

  return processBoundaries( std::move( x ), std::move( y ),
                            { x.size() > 0 ? x.size() - 1 : 0 },
                            { interpolant }, curate );
}

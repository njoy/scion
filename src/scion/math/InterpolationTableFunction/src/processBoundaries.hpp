/**
 *  @brief Verify and correct boundaries and interpolants
 *
 *  This function does a lot, so here's an overview of what it does. First of all, it verifies
 *  the following things:
 *    - There are at least 2 values in the x and f(y) grid
 *    - The x and f(y) grid have the same size
 *    - The number of boundaries and interpolants are the same
 *    - The last boundary index is equal to the index of the last x value
 *    - The x grid is sorted
 *    - There is no jump at the beginning or end of the x grid
 *    - The x values appear only a maximum of two times in the grid
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
 *  A jump at the end of the x grid is also not allowed.
 */
static std::tuple< std::vector< double >,
                   std::vector< F >,
                   std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( std::vector< X >&& x, std::vector< F >&& f,
                   std::vector< std::size_t >&& boundaries,
                   std::vector< interpolation::InterpolationType >&& interpolants  ) {

  if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
       ( ! verification::isAtLeastOfSize( f, 2 ) ) ) {

    Log::error( "Insufficient x values or f(y) functions defined for tabulated data "
                "(at least 2 points are required)" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "f.size(): {}", f.size() );
    throw std::exception();
  }

  if ( ! verification::isSameSize( x, f ) ) {

    Log::error( "Inconsistent number of x values and f(y) functions for tabulated data" );
    Log::info( "x.size(): {}", x.size() );
    Log::info( "f.size(): {}", f.size() );
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
  if ( xIter == x.begin() ) {

    Log::error( "A jump in the x grid cannot occur at the beginning of the x grid" );
    throw std::exception();
  }

  auto bIter = boundaries.begin();
  auto iIter = interpolants.begin();
  while ( xIter != x.end() ) {

    auto index = std::distance( x.begin(), xIter );
    bIter = std::lower_bound( bIter, boundaries.end(), index );
    if ( *bIter != index ) {

      if ( *bIter == index + 1 ) {

        *bIter -= 1;
      }
      else {

        iIter = std::next( interpolants.begin(),
                           std::distance( boundaries.begin(), bIter ) );
        bIter = boundaries.insert( bIter, index );
        iIter = interpolants.insert( iIter, *iIter );
      }
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

  return { std::move( x ), std::move( f ),
           std::move( boundaries ), std::move( interpolants ) };
}

static std::tuple< std::vector< X >,
                   std::vector< F >,
                   std::vector< std::size_t >,
                   std::vector< interpolation::InterpolationType > >
processBoundaries( std::vector< X >&& x, std::vector< F >&& f,
                   interpolation::InterpolationType interpolant ) {

  return processBoundaries( std::move( x ), std::move( f ),
                            { x.size() > 0 ? x.size() - 1 : 0 },
                            { interpolant } );
}
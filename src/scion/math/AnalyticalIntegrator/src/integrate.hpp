template < typename Y,
           typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
std::vector< I > integrate( const InterpolationTable< X, Y >& table ) const {

  if ( ! table.isLinearised() ) {

    Log::error( "Cannot perform analytical integration on a table that has not been linearised" );
    throw std::exception();
  }

  std::vector< I > result( this->boundaries().size() - 1, I( 0. ) );

  auto interpolator = interpolation::LinearLinear();
  auto integrator = integration::LinearLinear();

  auto gLeft = this->boundaries().begin();
  auto gRight = std::next( gLeft );
  auto iter = result.begin();

  auto xBegin = std::lower_bound( table.x().begin(), table.x().end(), *gLeft );
  if ( xBegin == table.x().end() ) {

    return result;
  }
  auto yBegin = std::next( table.y().begin(), std::distance( table.x().begin(), xBegin ) );

  while ( gRight != this->boundaries().end() ) {

    if ( *gRight < *xBegin ) {

      if ( xBegin != table.x().begin() ) {

        *iter += integrator( *gLeft, *gRight,
                             interpolator( *gLeft, *std::prev( xBegin ), *xBegin,
                                                   *std::prev( yBegin ), *yBegin ),
                             interpolator( *gRight, *std::prev( xBegin ), *xBegin,
                                                    *std::prev( yBegin ), *yBegin ) );
      }
    }
    else {

      if ( ( xBegin != table.x().begin() ) && ( *gLeft < *xBegin ) ) {

        *iter += integrator( *gLeft, *xBegin,
                             interpolator( *gLeft, *std::prev( xBegin ), *xBegin,
                                                   *std::prev( yBegin ), *yBegin ),
                             *yBegin );
      }
      ++xBegin;
      ++yBegin;

      while ( ( xBegin != table.x().end() ) && ( *xBegin < *gRight ) ) {

        *iter += integrator( *std::prev( xBegin ), *xBegin,
                             *std::prev( yBegin ), *yBegin );
        ++xBegin;
        ++yBegin;
      }

      if ( xBegin == table.x().end() ) {

        break;
      }
      else {

        if ( *gRight < *xBegin ) {

          *iter += integrator( *std::prev( xBegin ), *gRight,
                               *std::prev( yBegin ),
                               interpolator( *gRight,
                                             *std::prev( xBegin ), *xBegin,
                                             *std::prev( yBegin ), *yBegin ) );
        }
        else {

          *iter += integrator( *std::prev( xBegin ), *xBegin,
                               *std::prev( yBegin ), *yBegin );
        }
      }
    }

    ++iter;
    ++gLeft;
    ++gRight;
  }

  return result;
}

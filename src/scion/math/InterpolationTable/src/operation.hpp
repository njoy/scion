template < typename BinaryOperation >
InterpolationTable&
operationForLinearisedOnly( const Y& right, BinaryOperation operation ) {

  // tables need to be linearised for the operation to be performed
  if ( this->isLinearised() ) {

    std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                    [&right, &operation] ( auto&& y )
                                         { return operation( y, right ); } );

    return *this;
  }
  else {

    Log::error( "Cannot perform addition and subtraction of scalars on a table that has not been linearised" );
    throw std::exception();
  }
}

template < typename S, typename BinaryOperation >
InterpolationTable&
operation( const S& right, BinaryOperation operation ) {

  std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                  [&right, &operation] ( auto&& y )
                                       { return operation( y, right ); } );

  return *this;
}

template < typename BinaryOperation >
InterpolationTable&
operation( const InterpolationTable& right, BinaryOperation operation ) {

  // tables need to be linearised for the operation to be performed
  if ( this->isLinearised() && right.isLinearised() ) {

    // if they are already on the same grid just perform the operation
    if ( this->x() == right.x() ) {

      std::transform( this->y().begin(), this->y().end(), right.y().begin(),
                      this->y_.begin(), operation );
    }
    else {

      // unionise and evaluate on the new grid
      unionisation::Unioniser< std::vector< X > > unioniser;
      unioniser.addGrid( this->x(), this->y() );
      unioniser.addGrid( right.x(), right.y() );

      std::vector< X > x = unioniser.unionise();
      std::vector< Y > y = unioniser.evaluate( this->x(), this->y() );
      std::vector< Y > temp = unioniser.evaluate( right.x(), right.y() );
      std::transform( y.begin(), y.end(), temp.begin(), y.begin(), operation );

      // check for threshold jumps with the same y value and remove them
      auto xIter = std::adjacent_find( x.begin(), x.end() );
      while ( xIter != x.end() ) {

        auto yIter = std::next( y.begin(), std::distance( x.begin(), xIter ) );
        if ( *std::next( yIter ) == *yIter ) {

          xIter = x.erase( xIter );
          yIter = y.erase( yIter );
        }

        // find the next duplicate x value
        xIter = std::adjacent_find( std::upper_bound( xIter, x.end(), *xIter ), x.end() );
      }

      // replace this with a new table
      *this = InterpolationTable( std::move( x ), std::move( y ) );
    }

    return *this;
  }
  else {

    Log::error( "Cannot perform operation on tables that have not been linearised" );
    Log::info( "left linearised: {}", this->isLinearised() ? "yes" : "no" );
    Log::info( "right linearised: {}", right.isLinearised() ? "yes" : "no" );
    throw std::exception();
  }
}

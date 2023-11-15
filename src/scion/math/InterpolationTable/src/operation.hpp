template < typename BinaryOperation >
InterpolationTable& operation( const Y& right,
                               BinaryOperation operation ) {

  // tables need to be linearised for the operation to be performed
  if ( this->isLinearised() ) {

    std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                    [&right, &operation] ( auto&& y )
                                         { return operation( y, right ); } );

    return *this;
  }
  else {

    Log::error( "Cannot perform scalar operation on a table that has not been linearised" );
    throw std::exception();
  }
}

template < typename BinaryOperation >
InterpolationTable& operation( const InterpolationTable& right,
                               BinaryOperation operation ) {

  // tables need to be linearised for the operation to be performed
  if ( this->isLinearised() && right.isLinearised() ) {

    // if they are already on the same grid just perform the operation
    if ( this->x() == right.x() ) {

      std::transform( this->y().begin(), this->y().end(), right.y().begin(),
                      this->y_.begin(), operation );
    }
    else {

      // check for threshold tables
      if ( this->x().front() != right.x().front() ) {

        Y ystart = this->x().front() < right.x().front() ? right.y().front()
                                                         : this->y().front();

        if ( Y( 0. ) != ystart ) {

          X xstart = this->x().front() < right.x().front() ? right.x().front()
                                                           : this->x().front();

          Log::error( "The threshold table's first y value is not zero" );
          Log::info( "Found x = {}", xstart );
          Log::info( "Found y = {}", ystart );
          throw std::exception();
        }
      }

      // unionise and evaluate on the new grid
      std::vector< X > x = unionisation::unionise( this->x(), right.x() );
      std::vector< Y > y = this->evaluateOnGrid( x );
      std::vector< Y > temp = right.evaluateOnGrid( x );
      std::transform( y.begin(), y.end(), temp.begin(), y.begin(), operation );

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

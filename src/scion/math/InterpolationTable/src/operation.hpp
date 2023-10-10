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

    // if they are already on the same grid just sum the y values
    if ( this->x() == right.x() ) {

      std::transform( this->y().begin(), this->y().end(), right.y().begin(),
                      this->y_.begin(), operation );
    }
    else {

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

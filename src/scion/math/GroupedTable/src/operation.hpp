/**
 *  @brief Apply a binary operation involving a scalar of type Y
 *
 *  This function is applied to addition and subtraction
 */
template < typename BinaryOperation >
GroupedTable&
operationForAdditionAndSubtraction( const Y& right, BinaryOperation operation ) {

  std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                  [&right, &operation] ( auto&& y )
                                       { return operation( y, right ); } );

  return *this;
}

/**
 *  @brief Apply a binary operation involving a scalar
 *
 *  This function is applied to division and multiplication
 */
template < typename S, typename BinaryOperation >
GroupedTable&
operation( const S& right, BinaryOperation operation ) {

  std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                  [&right, &operation] ( auto&& y )
                                       { return operation( y, right ); } );

  return *this;
}

/**
 *  @brief Apply a binary operation involving another GroupedTable
 *
 *  This function is applied to addition and subtraction
 */
template < typename BinaryOperation >
GroupedTable&
operation( const GroupedTable& right, BinaryOperation operation ) {

  // we can only perform the operation if they have the same boundaries
  if ( this->boundaries() == right.boundaries() ) {

    std::transform( this->y_.cbegin(), this->y_.cend(), right.y_.begin(),
                    this->y_.begin(), operation );

    return *this;
  }
  else {

    Log::error( "The operation cannot be performed because both tables do not have the "
                "same boundaries" );
    Log::info( "left number of groups: {}", this->numberGroups() );
    Log::info( "right number of groups: {}", right.numberGroups() );
    throw std::exception();
  }
}

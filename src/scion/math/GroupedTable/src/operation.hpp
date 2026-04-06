template < typename S, typename BinaryOperation >
GroupedTable&
operation( const S& right, BinaryOperation operation ) {

  std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                  [&right, &operation] ( auto&& y )
                                       { return operation( y, right ); } );

  return *this;
}
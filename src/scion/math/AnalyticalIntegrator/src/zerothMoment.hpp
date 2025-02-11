template < typename Y,
           typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
std::vector< I > zerothMoment( const InterpolationTable< X, Y >& table ) const {

  return this->operator()( table );
}

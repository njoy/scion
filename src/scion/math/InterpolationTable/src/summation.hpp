/**
 *  @brief Calculate a summation over all interpolation regions
 */
template < typename Lambda >
auto summation( const Lambda& lambda ) const {

  auto iter = this->tables().begin();
  auto result = std::visit( lambda, *iter );
  ++iter;

  while ( iter != this->tables().end() ) {

    result += std::visit( lambda, *iter );
    ++iter;
  }

  return result;
}

#ifndef NJOY_SCION_VERIFICATION_RANGES
#define NJOY_SCION_VERIFICATION_RANGES

// system includes

// other includes

namespace njoy {
namespace scion {
namespace verification {

/** @brief Verify if two ranges are the same size
 *
 *  @param[in] left    the left range
 *  @param[in] right   the right range
 */
template < typename LeftRange, typename RightRange >
bool isSameSize( const LeftRange left, const RightRange& right ) {

  return std::size( left ) == std::size( right );
}

/** @brief Verify if a range is at least of a given size
 *
 *  @param[in] range    the range
 *  @param[in] size     the size
 */
template < typename Range >
bool isAtLeastOfSize( const Range& range, std::size_t size ) {

  return size <= std::size( range );
}

/** @brief Verify if a range is empty
 *
 *  @param[in] range    the range
 */
template < typename Range >
bool isEmpty( const Range& range ) {

  return 0 == std::size( range );
}

/** @brief Verify if a range is sorted
 *
 *  @param[in] range    the range
 */
template < typename Range >
bool isSorted( const Range& range ) {

  return std::is_sorted( range.begin(), range.end() );
}

/** @brief Verify if a range consists of unique elements
 *
 *  It is assumed that the range being tested is sorted.
 *
 *  @param[in] range    the range
 */
template < typename Range >
bool isUnique( const Range& range ) {

  return range.end() == std::adjacent_find( range.begin(), range.end() );
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

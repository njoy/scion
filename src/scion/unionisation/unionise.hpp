#ifndef NJOY_SCION_UNIONISATION_UNION
#define NJOY_SCION_UNIONISATION_UNION

// system includes

// other includes

namespace njoy {
namespace scion {
namespace unionisation {

  /**
   *  @brief Unionise two grids and preserve duplicate points that appear in each
   *
   *  Guess what: the STL library provides exactly what we need :-)
   *
   *  Caveat: duplicate values in both grids can only appear twice.
   *
   *  @param first        the first grid (assumed to be sorted)
   *  @param second       the second grid (assumed to be sorted)
   */
  template < typename X >
  std::vector< X >
  unionise( const std::vector< X >& first, const std::vector< X >& second ) {

    std::vector< X > grid( first.size() + second.size() );
    auto end = std::set_union( first.begin(), first.end(),
                               second.begin(), second.end(),
                               grid.begin() );
    grid.erase( end, grid.end() );
    return grid;
  }

} // unionisation namespace
} // scion namespace
} // njoy namespace

#endif

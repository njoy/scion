#ifndef NJOY_SCION_UNIONISATION_UNION
#define NJOY_SCION_UNIONISATION_UNION

// system includes
#include <algorithm>

// other includes

namespace njoy {
namespace scion {
namespace unionisation {

  /**
   *  @brief Unionise two grids and preserve duplicate points that appear in each
   *
   *  If the grids do not have the same end point, a duplicate point is inserted
   *  into the grid corresponding to the lowest end point (unless that is
   *  already a duplicate point).
   *
   *  @param first        the first grid (assumed to be sorted)
   *  @param second       the second grid (assumed to be sorted)
   */
  template < typename X >
  std::vector< X >
  unionise( const std::vector< X >& first, const std::vector< X >& second ) {

    // merge the two grids - keeping a maximum of 2 duplicates
    std::vector< X > grid( first.size() + second.size() );
    auto end = std::set_union( first.begin(), first.end(),
                               second.begin(), second.end(),
                               grid.begin() );
    grid.erase( end, grid.end() );

    // special case: the end points are not the same
    if ( first.back() != second.back() ) {

      X duplicate = first.back() < second.back() ? first.back() : second.back();
      auto iter = std::lower_bound( grid.begin(), grid.end(), duplicate );
      if ( *std::next( iter ) != duplicate ) {

        grid.insert( iter, duplicate );
      }
    }

    return grid;
  }

} // unionisation namespace
} // scion namespace
} // njoy namespace

#endif

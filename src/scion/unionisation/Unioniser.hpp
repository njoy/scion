#ifndef NJOY_SCION_UNIONISATION_UNIONISER
#define NJOY_SCION_UNIONISATION_UNIONISER

// system includes
#include <algorithm>
#include <functional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/LinearLinear.hpp"

namespace njoy {
namespace scion {
namespace unionisation {

  /**
   *  @class
   *  @brief A generic unionisation object
   */
  template < typename XContainer,
             typename XIter = typename XContainer::const_iterator >
  class Unioniser {

    /* type aliases */
    using X = typename std::decay< typename XContainer::value_type >::type;

    /* fields */
    std::vector< std::pair< XIter, XIter > > grids_;
    std::vector< X > union_;

    /* auxiliary function */

    /**
     *  @brief Unionise two grids and preserve duplicate points that appear in each
     *
     *  If the grids do not have the same begin and/or end point, a duplicate point
     *  is inserted into the grid corresponding to the highest beginning and/or
     *  lowest end point (unless those are already a duplicate point).
     *
     *  @param first    the first grid (assumed to be sorted)
     *  @param second   the second grid (assumed to be sorted)
     */
    static std::vector< X >
    apply_set_union( const XIter& first1, const XIter& last1,
                     const XIter& first2, const XIter& last2 ) {

      // merge the two grids - keeping a maximum of 2 duplicates
      // std::back_inserter is slightly less performant it would seem
      std::vector< X > grid( std::distance( first1, last1 ) +
                             std::distance( first2, last2 ) );
      auto end = std::set_union( first1, last1, first2, last2, grid.begin() );
      grid.erase( end, grid.end() );

      // special case: the begin points are not the same
      X xfirst = *first1;
      X xsecond = *first2;
      if ( xfirst != xsecond ) {

        X x = std::max( xfirst, xsecond );
        auto iter = std::lower_bound( grid.begin(), grid.end(), x );
        if ( *std::next( iter ) != x ) {

          grid.insert( iter, x );
        }
      }

      // special case: the end points are not the same
      xfirst = *std::prev( last1 );
      xsecond = *std::prev( last2 );
      if ( xfirst != xsecond ) {

        X x = std::min( xfirst, xsecond );
        auto iter = std::lower_bound( grid.begin(), grid.end(), x );
        if ( *std::next( iter ) != x ) {

          grid.insert( iter, x );
        }
      }

      return grid;
    }

  public:

    /* constructor */
    #include "scion/unionisation/Unioniser/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Add a grid to be used in the unionisation process
     *
     *  @param[in] grid   the grid to be added
     */
    void addGrid( const XContainer& grid ) {

      this->grids_.emplace_back( grid.begin(), grid.end() );
    }

    /**
     *  @brief Perform the unionisation process and return the unionised grid
     */
    const std::vector< X >& unionise() {

      // sort the grids as a function of size
      std::sort( this->grids_.begin(), this->grids_.end(),
                 [] ( auto&& left, auto&& right )
                    { return std::distance( left.first, left.second ) <
                             std::distance( right.first, right.second ); } );

      // generate a first union grid
      this->union_ = apply_set_union( this->grids_[0].first, this->grids_[0].second,
                                      this->grids_[1].first, this->grids_[1].second );
      this->grids_.erase( this->grids_.begin(), this->grids_.begin() + 1 );

      // iterate over the remaining grids
      while ( this->grids_.size() > 0 ) {

        this->union_ = apply_set_union( this->grids_[0].first, this->grids_[0].second,
                                        this->union_.begin(), this->union_.end() );
        this->grids_.erase( this->grids_.begin() );
      }

      // return the final grid
      return this->union_;
    }

    /**
     *  @brief Return the final unionised grid
     */
    const std::vector< X >& grid() const {

      return this->union_;
    }

    /**
     *  @brief Return whether or not a grid is compatible with the unionised grid
     *
     *  A grid is only compatible with the unionised grid if all points in the
     *  the grid are present in the unionised grid. This function can be used
     *  prior to calling the evaluate() function to ensure that the contraints for
     *  that function are met (putting this test in the generate() function would
     *  cause too much overhead there).
     *
     *  @param[in] grid   the grid to be verified
     */
    bool isComptatible( const XContainer& grid ) const {

      auto find = [this] ( auto&& value ) {

        return std::binary_search( this->grid().begin(), this->grid().end(), value );
      };

      return std::all_of( grid.begin(), grid.end(), find );
    }

    /**
     *  @brief Evaluate a set of tabulated values on the unionised grid
     *
     *  This function assumes that all values in the x grid of the table
     *  are contained in the unionised grid. This assumption is NOT verified
     *  in this function since it would introduce too much overhead that might
     *  not be necessary (e.g. when the user is actually paying attention to what
     *  they are doing).
     *
     *  This function also assumes that the tabulated values can be interpolated
     *  linearly.
     *
     *  @param[in] x   the x grid of the table
     *  @param[in] y   the y grid of the table
     */
    template < typename YContainer = XContainer,
               typename Y = typename std::decay< typename YContainer::value_type >::type >
    std::vector< Y > evaluate( const XContainer& x, const YContainer& y ) const {

      std::vector< Y > result( this->grid().size(), Y( 0. ) );

      auto xIter = std::lower_bound( this->grid().begin(), this->grid().end(), x.front() );
      if ( *std::next( xIter ) == x.front() ) {

        // move to the next x value in case of a jump
        ++xIter;
      }
      auto yIter = std::next( result.begin(), std::distance( this->grid().begin(), xIter ) );

      auto xTable = x.begin();
      auto yTable = y.begin();

      for ( ; xIter != this->grid().end(); ++xIter ) {

        if ( *xIter < *xTable ) {

          //! @todo extend this to any interpolation type?
          *yIter = interpolation::linlin( *xIter, *std::prev( xTable ), *xTable,
                                                  *std::prev( yTable ), *yTable );
        }
        else {

          *yIter = *yTable;
          ++xTable;
          ++yTable;

          if ( x.end() == xTable ) {

            break;
          }
        }
        ++yIter;
      }

      return result;
    }

    /**
     *  @brief Clear all objects in the unioniser
     */
    void clear() {

      this->grids_.clear();
      this->union_.clear();
    }
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

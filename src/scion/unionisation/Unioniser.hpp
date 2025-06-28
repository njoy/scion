#ifndef NJOY_SCION_UNIONISATION_UNIONISER
#define NJOY_SCION_UNIONISATION_UNIONISER

// system includes
#include <algorithm>
#include <functional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/Histogram.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"

namespace njoy {
namespace scion {
namespace unionisation {

  /**
   *  @class
   *  @brief A generic unionisation object
   *
   *  This class allows us to generate a union grid based on a given set of
   *  grids, and then reevaluate existing tabulated data on the final grid.
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
     *  @brief Sort the underlying grids as a function of size
     */
    void sort() {

      // sort the grids as a function of size
      std::sort( this->grids_.begin(), this->grids_.end(),
                 [] ( auto&& left, auto&& right )
                    { return std::distance( left.first, left.second ) <
                             std::distance( right.first, right.second ); } );
    }

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

      // merge the two grids
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

      auto size = std::distance( grid.begin(), grid.end() );
      this->grids_.insert(
          std::lower_bound( this->grids_.begin(), this->grids_.end(),
                            size,
                            [] ( auto&& pair, auto&& size )
                               { return std::distance( pair.first, pair.second ) < size; } ),
          std::make_pair( grid.begin(), grid.end() ) );
    }

    /**
     *  @brief Perform the unionisation process and return the unionised grid
     */
    const std::vector< X >& unionise() {

      // generate a first union grid
      this->union_ = std::vector< X >( this->grids_.front().first, this->grids_.front().second );
      this->grids_.erase( this->grids_.begin() );

      // iterate over the remaining grids
      while ( this->grids_.size() > 0 ) {

        this->union_ = apply_set_union( this->grids_.front().first, this->grids_.front().second ,
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
     *  the grid are present in the unionised grid. If the grid has duplicate points,
     *  those points must have duplicates in the unionised grid. If the start and/or end
     *  point of the grid and the unionised grid are not the same, then those points
     *  must have duplicates in the unionised grid. This function can be used
     *  prior to calling the evaluate() function to ensure that the contraints for
     *  that function are met (putting this test in the generate() function would
     *  cause too much overhead in that function so we decided against that).
     *
     *  @param[in] grid   the grid to be verified
     */
    bool isComptatible( const XContainer& grid ) const {

      // check if all values are in the unionised grid
      auto find = [this] ( auto&& value ) {

        return std::binary_search( this->grid().begin(), this->grid().end(), value );
      };

      if ( std::all_of( grid.begin(), grid.end(), find ) ) {

        // check if all jumps in the grid are in the unionised grid
        auto iter = std::adjacent_find( grid.begin(), grid.end() );
        while ( iter != grid.end() ) {

          // the element is present at least once in the unionised grid
          // (checked with std::all_of) so lower bound always points to
          // the value we are looking for. lower_bound can never return
          // end() for the same reason.
          auto lower = std::lower_bound( this->grid().begin(), this->grid().end(), *iter );
          auto upper = std::upper_bound( lower, this->grid().end(), *iter );
          if ( 1 >= std::distance( lower, upper ) ) {

            return false;
          }

          // find the next duplicate
          iter = std::adjacent_find( std::upper_bound( iter, grid.end(), *iter ), grid.end() );
        }

        // check front value in the grid
        iter = std::lower_bound( this->grid().begin(), this->grid().end(), grid.front() );
        if ( iter != this->grid().begin() ) {

          // check for jump
          auto upper = std::upper_bound( iter, this->grid().end(), grid.front() );
          if ( 1 >= std::distance( iter, upper ) ) {

            return false;
          }
        }

        // check back value in the grid
        iter = std::lower_bound( this->grid().begin(), this->grid().end(), grid.back() );
        if ( iter != std::prev( this->grid().end() ) ) {

          // check for jump
          auto upper = std::upper_bound( iter, this->grid().end(), grid.back() );
          if ( 1 >= std::distance( iter, upper ) ) {

            return false;
          }
        }

        return true;
      }
      else {

        return false;
      }
    }

    /**
     *  @brief Evaluate a set of tabulated values on the unionised grid
     *
     *  This function assumes that all values in the x grid of the table
     *  are contained in the unionised grid and that all necessary jumps are
     *  present. This assumption is NOT verified in this function since it
     *  would introduce too much overhead that might not be necessary (e.g.
     *  when the user is actually paying attention to what they are doing).
     *
     *  @param[in] x              the x grid of the table
     *  @param[in] y              the y grid of the table
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     */
    template < typename BContainer,
               typename IContainer,
               typename YContainer = XContainer,
               typename Y = typename std::decay< typename YContainer::value_type >::type >
    std::vector< Y > evaluate( const XContainer& x, const YContainer& y,
                               const BContainer& boundaries,
                               const IContainer& interpolants ) const {

      std::vector< Y > result( this->grid().size(), Y( 0. ) );

      auto xIter = std::lower_bound( this->grid().begin(), this->grid().end(), x.front() );
      if ( *std::next( xIter ) == x.front() ) {

        // move to the next x value in case of a jump
        ++xIter;
      }
      auto yIter = std::next( result.begin(), std::distance( this->grid().begin(), xIter ) );

      auto xTable = x.begin();
      auto yTable = y.begin();
      auto bTable = boundaries.begin();
      auto iTable = interpolants.begin();

      std::size_t current = 0;
      for ( ; xIter != this->grid().end(); ++xIter ) {

        if ( *xIter < *xTable ) {

          switch ( *iTable ) {

            case interpolation::InterpolationType::Histogram : {

              *yIter = interpolation::histogram( *xIter, *std::prev( xTable ), *xTable,
                                                         *std::prev( yTable ), *yTable );
              break;
            }
            case interpolation::InterpolationType::LinearLinear : {

              *yIter = interpolation::linlin( *xIter, *std::prev( xTable ), *xTable,
                                                      *std::prev( yTable ), *yTable );
              break;
            }
            case interpolation::InterpolationType::LogLinear : {

              *yIter = interpolation::loglin( *xIter, *std::prev( xTable ), *xTable,
                                                      *std::prev( yTable ), *yTable );
              break;
            }
            case interpolation::InterpolationType::LinearLog : {

              *yIter = interpolation::linlog( *xIter, *std::prev( xTable ), *xTable,
                                                      *std::prev( yTable ), *yTable );
              break;
            }
            case interpolation::InterpolationType::LogLog : {

              *yIter = interpolation::loglog( *xIter, *std::prev( xTable ), *xTable,
                                                      *std::prev( yTable ), *yTable );
              break;
            }
            default : {

              Log::error( "Unreachable code" );
              throw std::exception();
            }
          }
        }
        else {

          *yIter = *yTable;
          ++xTable;
          ++yTable;
          ++current;

          if ( x.end() == xTable ) {

            break;
          }

          if ( current > *bTable ) {

            ++bTable;
            ++iTable;
          }
        }
        ++yIter;
      }

      return result;
    }

    /**
     *  @brief Evaluate a set of tabulated values on the unionised grid
     *
     *  This function assumes that all values in the x grid of the table
     *  are contained in the unionised grid and that all necessary jumps are
     *  present. This assumption is NOT verified in this function since it
     *  would introduce too much overhead that might not be necessary (e.g.
     *  when the user is actually paying attention to what they are doing).
     *
     *  @param[in] x              the x grid of the table
     *  @param[in] y              the y grid of the table
     *  @param[in] interpolant    the interpolation type of the table (default lin-lin)
     */
    template < typename YContainer = XContainer,
               typename Y = typename std::decay< typename YContainer::value_type >::type >
    std::vector< Y > evaluate( const XContainer& x, const YContainer& y,
                               interpolation::InterpolationType interpolant =
                                 interpolation::InterpolationType::LinearLinear ) const {

      return evaluate(
               x, y,
               std::vector< std::size_t >{ static_cast< std::size_t >( std::distance( x.begin(), x.end() ) ) },
               std::vector< interpolation::InterpolationType >{ interpolant } );
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

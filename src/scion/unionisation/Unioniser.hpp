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

    /* helper class */

    struct GridInformation {

      XIter begin;
      XIter end;
      bool first_value_is_zero;
      bool last_value_is_zero;
    };

    /* fields */
    std::vector< GridInformation > grids_;

    std::vector< X > union_;
    bool firstZero_;
    bool lastZero_;

    /* auxiliary function */

    /**
     *  @brief Sort the underlying grids as a function of size
     */
    void sort() {

      // sort the grids as a function of size
      std::sort( this->grids_.begin(), this->grids_.end(),
                 [] ( auto&& left, auto&& right )
                    { return std::distance( left.begin, left.end ) <
                             std::distance( right.begin, right.end ); } );
    }

    /**
     *  @brief Unionise two grids and preserve duplicate points that appear in each
     *
     *  @param first1   an iterator to the first element of the first grid
     *  @param last1    an iterator pointing past the last element of the first grid
     *  @param first2   an iterator to the first element of the second grid
     *  @param last2    an iterator pointing past the last element of the second grid
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

      return grid;
    }

    /**
     *  @brief Add a jump if required
     *
     *  If the grids do not have the same begin point, a duplicate point is inserted into
     *  the grid corresponding to the highest beginning point (unless those are already
     *  a duplicate point) if the corresponding tabulated values are non-zero.
     *
     *  @param first1   an iterator to the first element of the first grid
     *  @param first2   an iterator to the first element of the second grid
     *  @param zero1    true if the first value of the first grid is zero
     *  @param zero2    true if the first value of the second grid is zero
     */
    bool add_first_jump( std::vector< X >& grid,
                         const XIter& first1, const XIter& first2,
                         bool zero1, bool zero2 ) {

      // special case: the begin points are not the same
      X xfirst = *first1;
      X xsecond = *first2;
      if ( xfirst != xsecond ) {

        bool check = xfirst < xsecond;

        bool zero = check ? zero2 : zero1;
        bool result = check ? zero1 : zero2;

        if ( ! zero ) {

          X x = check ? xsecond : xfirst;
          auto iter = std::lower_bound( grid.begin(), grid.end(), x );
          if ( *std::next( iter ) != x ) {

            grid.insert( iter, x );
          }
        }

        return result;
      }
      else {

        return zero1 && zero2;
      }
    }

    /**
     *  @brief Add a jump if required
     *
     *  If the grids do not have the same end point, a duplicate point is inserted into
     *  the grid corresponding to the lowest end point (unless those are already a
     *  duplicate point) if the corresponding tabulated values are non-zero.
     *
     *  @param first1   an iterator to past the last element of the first grid
     *  @param first2   an iterator to past the last element of the second grid
     *  @param zero1    true if the last value of the first grid is zero
     *  @param zero2    true if the last value of the second grid is zero
     */
    bool add_last_jump( std::vector< X >& grid,
                        const XIter& last1, const XIter& last2,
                        bool zero1, bool zero2 ) {

      // special case: the end points are not the same
      X xfirst = *std::prev( last1 );
      X xsecond = *std::prev( last2 );
      if ( xfirst != xsecond ) {

        bool check = xfirst < xsecond;

        bool zero = check ? zero1 : zero2;
        bool result = check ? zero2 : zero1;

        if ( ! zero ) {

          X x = check ? xfirst : xsecond;
          auto iter = std::lower_bound( grid.begin(), grid.end(), x );
          if ( *std::next( iter ) != x ) {

            grid.insert( iter, x );
          }
        }

        return result;
      }
      else {

        return zero1 && zero2;
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor
     */
    Unioniser() = default;

    /* methods */

    /**
     *  @brief Add a grid to be used in the unionisation process
     *
     *  @param[in] grid     the grid to be added
     *  @param[in] values   the associated tabulated values
     */
    template < typename YContainer = XContainer,
               typename Y = typename std::decay< typename YContainer::value_type >::type >
    void addGrid( const XContainer& grid, const YContainer& values ) {

      auto is_zero = [] ( auto&& iter ) { return *iter == Y(); };

      auto begin = std::begin( grid );
      auto end = std::end( grid );

      auto size = std::distance( begin, end );
      this->grids_.insert(
          std::lower_bound( this->grids_.begin(), this->grids_.end(), size,
                            [] ( auto&& grid, auto&& size )
                               { return std::distance( grid.begin, grid.end ) < size; } ),
          GridInformation{ begin, end,
                           is_zero( std::begin( values ) ),
                           is_zero( std::prev( std::end( values ) ) ) } );
    }

    /**
     *  @brief Perform the unionisation process and return the unionised grid
     */
    const std::vector< X >& unionise() {

      // generate a first union grid
      if ( this->grids_.size() > 1 ) {

        this->union_ = apply_set_union( this->grids_[0].begin, this->grids_[0].end,
                                        this->grids_[1].begin, this->grids_[1].end );
        this->firstZero_ = add_first_jump( this->union_, this->grids_[0].begin, this->grids_[1].begin,
                                           this->grids_[0].first_value_is_zero, this->grids_[1].first_value_is_zero );
        this->lastZero_ = add_last_jump( this->union_, this->grids_[0].end, this->grids_[1].end,
                                           this->grids_[0].last_value_is_zero, this->grids_[1].last_value_is_zero );
        this->grids_.erase( this->grids_.begin(), this->grids_.begin() + 2 );
      }
      else if ( this->grids_.size() == 1 ) {

        this->union_ = std::vector< X >{ this->grids_[0].begin, this->grids_[0].end };
        this->grids_.erase( this->grids_.begin() );
      }

      // iterate over the remaining grids
      while ( this->grids_.size() > 0 ) {

        this->union_ = apply_set_union( this->grids_.front().begin,
                                        this->grids_.front().end,
                                        this->union_.begin(), this->union_.end() );
        this->firstZero_ = add_first_jump( this->union_, this->grids_.front().begin, this->union_.begin(),
                                           this->grids_.front().first_value_is_zero, this->firstZero_ );
        this->lastZero_ = add_last_jump( this->union_, this->grids_.front().end, this->union_.end(),
                                           this->grids_.front().last_value_is_zero, this->lastZero_ );
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
     *  must have duplicates in the unionised grid if the corresponding y values are
     *  different from zero. This function can be used prior to calling the evaluate()
     *  function to ensure that the contraints for that function are met (putting this
     *  test in the generate() function would cause too much overhead in that function
     *  so we decided against that).
     *
     *  @param[in] grid   the grid to be verified
     */
    template < typename YContainer = XContainer,
               typename Y = typename std::decay< typename YContainer::value_type >::type >
    bool isComptatible( const XContainer& grid, const YContainer& values ) const {

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

          // check for jump if the front y value is non-zero
          if ( values.front() != Y() ) {

            auto upper = std::upper_bound( iter, this->grid().end(), grid.front() );
            if ( 1 >= std::distance( iter, upper ) ) {

              return false;
            }
          }
        }

        // check back value in the grid
        iter = std::lower_bound( this->grid().begin(), this->grid().end(), grid.back() );
        if ( iter != std::prev( this->grid().end() ) ) {

          // check for jump if the back y value is non-zero
          if ( values.back() != Y() ) {

            auto upper = std::upper_bound( iter, this->grid().end(), grid.back() );
            if ( 1 >= std::distance( iter, upper ) ) {

              return false;
            }
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
    std::vector< Y > evaluate( const XContainer& x,
                               const YContainer& y,
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
     *  @brief Update the boundaries and interpolants
     *
     *  @param[in] x              the x grid of the table
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     */
    template < typename BContainer, typename IContainer >
    std::pair< std::vector< std::size_t >, std::vector< interpolation::InterpolationType > >
    updateBoundariesAndInterpolants( const XContainer& x,
                                     const BContainer& boundaries,
                                     const IContainer& interpolants ) const {

      std::vector< std::size_t > newboundaries;
      std::vector< interpolation::InterpolationType > newinterpolants( interpolants.begin(), interpolants.end() );

      // if necessay: add a lin-lin region in front if the old grid did not start at
      // the same values as the new grid
      if ( x.front() != this->grid().front() ) {

        if ( newinterpolants.front() != interpolation::InterpolationType::LinearLinear ) {

          auto iter = std::lower_bound( this->grid().begin(), this->grid().end(), x.front() );
          newboundaries.push_back( std::distance( this->grid().begin(), iter ) );
          newinterpolants.insert( newinterpolants.begin(), interpolation::InterpolationType::LinearLinear );
        }
      }

      for ( const auto& index : boundaries ) {

        auto iter = std::lower_bound( this->grid().begin(), this->grid().end(), x[index] );
        newboundaries.push_back( std::distance( this->grid().begin(), iter ) );
      }

      // if necessay: add a lin-lin region at the end if the old grid did not end at
      // the same values as the new grid
      if ( newboundaries.back() != this->grid().size() - 1 ) {

        if ( newinterpolants.back() != interpolation::InterpolationType::LinearLinear ) {

          newboundaries.push_back( this->grid().size() - 1 );
          newinterpolants.push_back( interpolation::InterpolationType::LinearLinear );
        }
        else {

          newboundaries.back() = this->grid().size() - 1;
        }
      }

      return std::make_pair( std::move( newboundaries ), std::move( newinterpolants ) );
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

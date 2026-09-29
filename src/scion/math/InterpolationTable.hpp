#ifndef NJOY_SCION_MATH_INTERPOLATIONTABLE
#define NJOY_SCION_MATH_INTERPOLATIONTABLE

// system includes
#include <algorithm>
#include <tuple>
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "utility/IteratorView.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/unionisation/Unioniser.hpp"
#include "scion/math/newton.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/HistogramTable.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "scion/math/LinearLogTable.hpp"
#include "scion/math/LogLinearTable.hpp"
#include "scion/math/LogLogTable.hpp"
#include "scion/math/IntervalDomain.hpp"
#include "scion/verification/ranges.hpp"

#include "scion/math/ConstantWeightFunction.hpp"
#include "scion/math/MeanWeightFunction.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with one or more interpolation types
   */
  template < typename X, typename Y >
  class InterpolationTable :
      public OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y > {

    /* friend declarations */

    friend class OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y >;

    /* type aliases */

    using Parent = OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y >;
    using XIterator = typename std::vector< X >::const_iterator;
    using YIterator = typename std::vector< Y >::const_iterator;
    using XContainer = njoy::utility::IteratorView< XIterator >;
    using YContainer = njoy::utility::IteratorView< YIterator >;
    using TableVariant = std::variant<
                             LinearLinearTable< X, Y, XContainer, YContainer >,
                             HistogramTable< X, Y, XContainer, YContainer >,
                             LinearLogTable< X, Y, XContainer, YContainer >,
                             LogLinearTable< X, Y, XContainer, YContainer >,
                             LogLogTable< X, Y, XContainer, YContainer > >;

    struct ProcessedData {

      std::vector< X > x;
      std::vector< Y > y;
      std::vector< std::size_t > boundaries;
      std::vector< interpolation::InterpolationType > interpolants;
      bool linearised;
      bool curated;
    };

    /* fields */

    std::vector< X > x_;
    std::vector< Y > y_;
    std::vector< std::size_t > boundaries_;
    std::vector< interpolation::InterpolationType > interpolants_;
    bool linearised_;
    bool curated_;

    std::vector< TableVariant > tables_;

    /* auxiliary function */

    template < typename BinaryOperation >
    InterpolationTable&
    operationForLinearisedOnly( const Y& right, BinaryOperation operation ) {

      // tables need to be linearised for the operation to be performed
      if ( this->isLinearised() ) {

        std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                        [&right, &operation] ( auto&& y )
                                             { return operation( y, right ); } );

        return *this;
      }
      else {

        Log::error( "Cannot perform addition and subtraction of scalars on a table that has not been linearised" );
        throw std::exception();
      }
    }

    template < typename S, typename BinaryOperation >
    InterpolationTable&
    operation( const S& right, BinaryOperation operation ) {

      std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                      [&right, &operation] ( auto&& y )
                                           { return operation( y, right ); } );

      return *this;
    }

    template < typename BinaryOperation >
    InterpolationTable&
    operation( const InterpolationTable& right, BinaryOperation operation ) {

      // tables need to be linearised for the operation to be performed
      if ( this->isLinearised() && right.isLinearised() ) {

        // if they are already on the same grid just perform the operation
        if ( this->x() == right.x() ) {

          std::transform( this->y().begin(), this->y().end(), right.y().begin(),
                          this->y_.begin(), operation );
        }
        else {

          // unionise and evaluate on the new grid
          unionisation::Unioniser< std::vector< X > > unioniser;
          unioniser.addGrid( this->x(), this->y() );
          unioniser.addGrid( right.x(), right.y() );

          std::vector< X > x = unioniser.unionise();
          std::vector< Y > y = unioniser.evaluate( this->x(), this->y() );
          std::vector< Y > temp = unioniser.evaluate( right.x(), right.y() );
          std::transform( y.begin(), y.end(), temp.begin(), y.begin(), operation );

          // check for threshold jumps with the same y value and remove them
          auto xIter = std::adjacent_find( x.begin(), x.end() );
          while ( xIter != x.end() ) {

            auto yIter = std::next( y.begin(), std::distance( x.begin(), xIter ) );

            auto xNext = std::upper_bound( xIter, x.end(), *xIter );
            auto yNext = std::next( yIter, std::distance( xIter, xNext ) );

            if ( std::all_of( std::next( yIter ), yNext,
                              [&] ( auto&& value ) { return value == *yIter; } ) ) {

              xNext = x.erase( std::next( xIter ), xNext );
              yNext = y.erase( std::next( yIter ), yNext );
            }

            // find the next duplicate x value
            xIter = std::adjacent_find( xNext, x.end() );
          }

          // replace this with a new table
          *this = InterpolationTable( std::move( x ), std::move( y ) );
        }

        return *this;
      }
      else {

        Log::error( "Cannot perform operation on tables that have not been linearised" );
        Log::info( "left linearised: {}", this->isLinearised() ? "yes" : "no" );
        Log::info( "right linearised: {}", right.isLinearised() ? "yes" : "no" );
        throw std::exception();
      }
    }

    void generateTables() {

      std::vector< TableVariant > tables;

      auto xStart = this->x().begin();
      auto yStart = this->y().begin();
      std::size_t nr = this->boundaries().size();
      for ( std::size_t i = 0; i < nr; ++i ) {

        auto xEnd = this->x().begin();
        auto yEnd = this->y().begin();
        std::advance( xEnd, this->boundaries()[i] + 1 );
        std::advance( yEnd, this->boundaries()[i] + 1 );

        switch ( this->interpolants()[i] ) {

          case interpolation::InterpolationType::LinearLinear : {

            tables.emplace_back(
              LinearLinearTable< X, Y, XContainer, YContainer >(
                XContainer( xStart, xEnd ),
                YContainer( yStart, yEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::Histogram : {

            tables.emplace_back(
              HistogramTable< X, Y, XContainer, YContainer >(
                XContainer( xStart, xEnd ),
                YContainer( yStart, yEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LinearLog : {

            tables.emplace_back( LinearLogTable< X, Y, XContainer, YContainer >(
                XContainer( xStart, xEnd ),
                YContainer( yStart, yEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LogLinear : {

            tables.emplace_back( LogLinearTable< X, Y, XContainer, YContainer >(
                XContainer( xStart, xEnd ),
                YContainer( yStart, yEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LogLog : {

            tables.emplace_back( LogLogTable< X, Y, XContainer, YContainer >(
                XContainer( xStart, xEnd ),
                YContainer( yStart, yEnd ) ) );
            break;
          }
          default : {

            Log::error( "Unsupported interpolation type for InterpolationTable" );
            throw std::exception();
          }
        }

        // don't do this for the last region: valgrind will yell at you
        if ( xEnd != this->x().end() ) {

          // go back to the shared boundary if there is no jump or advance to the last
          // point in the jump if there is one

          std::swap( xStart, xEnd );
          std::swap( yStart, yEnd );
          if ( *xStart > *std::prev( xStart ) ) {

            --xStart;
            --yStart;
          }
          else {

            auto iter = std::prev( std::upper_bound( xStart, this->x().end(), *xStart ) );
            auto offset = std::distance( xStart, iter );
            std::advance( xStart, offset );
            std::advance( yStart, offset );
          }
        }
      }

      this->tables_ = std::move( tables );
    }

    /**
     *  @brief Curate the tabulated data
     *
     *  Curation currently consists of removing extraneous interior points in discontinuities
     *  in the data.
     *
     *  The boundaries array is assumed to already have a boundary index pointing to the first
     *  point of every jump. This is guaranteed by processData() prior to calling this
     *  function. As a result, only the boundaries need to be checked to find the jumps.
     *
     *  The extraneous points are removed in a single pass by moving points that are kept forward
     *  over the extraneous points. The remaining points at the end are erased.
     */
    static void curateTable( std::vector< X >& x, std::vector< Y >& y,
                             std::vector< std::size_t >& boundaries,
                             std::vector< interpolation::InterpolationType >& /* interpolants */ ) {

      auto xRead = x.begin();
      auto yRead = y.begin();
      auto xWrite = x.begin();
      auto yWrite = y.begin();
      std::size_t removed = 0;
      for ( auto& boundary : boundaries ) {

        // the points up to and including the boundary point are kept
        auto xEnd = std::next( x.begin(), boundary + 1 );
        auto yEnd = std::next( y.begin(), boundary + 1 );

        // look for extraneous points in a jump starting at the boundary point
        std::size_t extraneous = 0;
        if ( ( xEnd != x.end() ) && ( *xEnd == *std::prev( xEnd ) ) ) {

          auto xNext = std::upper_bound( xEnd, x.end(), *xEnd );
          auto number = std::distance( std::prev( xEnd ), xNext );
          if ( number > 2 ) {

            Log::warning( "x = {} is present {} times, extraneous points will be removed", *xEnd, number );
            extraneous = number - 2;
          }
        }

        // move the points that are kept (nothing needs to move until a point was removed)
        if ( removed > 0 ) {

          xWrite = std::move( xRead, xEnd, xWrite );
          yWrite = std::move( yRead, yEnd, yWrite );
        }
        else {

          xWrite = xEnd;
          yWrite = yEnd;
        }
        xRead = std::next( xEnd, extraneous );
        yRead = std::next( yEnd, extraneous );

        boundary -= removed;
        removed += extraneous;
      }

      x.erase( xWrite, x.end() );
      y.erase( yWrite, y.end() );
    }

    /**
     *  @brief Verify and correct boundaries and interpolants
     *
     *  This function does a lot, so here's an overview of what it does. First of all, it verifies
     *  the following things:
     *    - There are at least 2 values in the x and y grid
     *    - The x and y grid have the same size
     *    - The number of boundaries and interpolants are the same
     *    - The last boundary index is equal to the index of the last x value
     *    - The x grid is sorted
     *
     *  Next, this function will look for every jump in the x grid and check if the jump corresponds
     *  to a change in interpolation region (meaning that the index of the first x value in the jump
     *  is in the boundaries). If that is not the case, an additional interpolation region wil be
     *  inserted. This ensures that none of the interpolation regions will contain a jump in their
     *  local x grid.
     *
     *  In some cases, the boundary values can point to the second point of a jump. While this is not
     *  an error (we will never interpolate on a jump), we need the boundaries to point to the first
     *  point in the jump instead of the second one. When this is encountered, the boundary value is
     *  adjusted. This change is made silently as it does not constitute an error on the user side.
     *
     *  A jump at the beginning or end of the x grid is allowed. However, if one of these jumps is
     *  detected, then the first or last point is just removed.
     *
     *  If curate is true, discontinuities of more than 2 points are reduced to the first and last
     *  point of the jump.
     */
    static ProcessedData
    processData( std::vector< X >&& x, std::vector< Y >&& y,
                 std::vector< std::size_t >&& boundaries,
                 std::vector< interpolation::InterpolationType >&& interpolants,
                 bool curate = false ) {

      if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
           ( ! verification::isAtLeastOfSize( y, 2 ) ) ) {

        Log::error( "Insufficient x or y values defined for tabulated data "
                    "(at least 2 points are required)" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "y.size(): {}", y.size() );
        throw std::exception();
      }

      if ( ! verification::isSameSize( x, y ) ) {

        Log::error( "Inconsistent number of x and y values for tabulated data" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "y.size(): {}", y.size() );
        throw std::exception();
      }

      if ( ! verification::isSameSize( boundaries, interpolants ) ) {

        Log::error( "Inconsistent number of boundaries and interpolants for tabulated data" );
        Log::info( "boundaries.size(): {}", boundaries.size() );
        Log::info( "interpolants.size(): {}", interpolants.size() );
        throw std::exception();
      }

      if ( boundaries.back() != x.size() - 1 ) {

        Log::error( "The last boundary value does not point to the last x value" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "boundaries.back(): {}", boundaries.back() );
        throw std::exception();
      }

      if ( ! verification::isSorted( x ) ) {

        Log::error( "The x values do not appear to be in ascending order" );
        throw std::exception();
      }

      bool curated = true;

      auto xIter = std::adjacent_find( x.begin(), x.end() );
      auto bIter = boundaries.begin();
      auto iIter = interpolants.begin();
      while ( xIter != x.end() ) {

        // determine the next x value
        auto xNext = std::upper_bound( xIter, x.end(), *xIter );
        auto number = std::distance( xIter, xNext );

        if ( ( xIter != x.begin() ) && ( xNext != x.end() ) && ( number > 2 ) ) {

          curated = false;
        }

        // set the boundary for this jump, insert it if necessary
        // index is always positive since xIter is x.begin() or higher iterator
        std::size_t index = std::distance( x.begin(), xIter );
        bIter = std::lower_bound( bIter, boundaries.end(), index );
        if ( *bIter != index ) {

          if ( *bIter < index + number ) {

            *bIter = index;
          }
          else {

            iIter = std::next( interpolants.begin(),
                               std::distance( boundaries.begin(), bIter ) );
            bIter = boundaries.insert( bIter, index );
            iIter = interpolants.insert( iIter, *iIter );
          }
        }

        xIter = std::adjacent_find( xNext, x.end() );
      }

      if ( curate ) {

        curateTable( x, y, boundaries, interpolants );
        curated = true;
      }

      // check for a jump at the beginning of the table (all but the last point are removed)
      xIter = x.begin();
      if ( *xIter == *( std::next( xIter ) ) ) {

        Log::warning( "A jump at the beginning of the table (x = {}) has been removed", *xIter );
        auto offset = std::distance( x.begin(), std::upper_bound( x.begin(), x.end(), *xIter ) ) - 1;
        x.erase( x.begin(), std::next( x.begin(), offset ) );
        y.erase( y.begin(), std::next( y.begin(), offset ) );
        boundaries.erase( boundaries.begin() );
        interpolants.erase( interpolants.begin() );
        std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                        [offset] ( auto&& boundary ) { return boundary - offset; } );
      }

      // check for a jump at the end of the table (all but the first point are removed)
      xIter = std::prev( x.end() );
      if ( *xIter == *( std::prev( xIter ) ) ) {

        Log::warning( "A jump at the end of the table (x = {}) has been removed", *xIter );
        auto offset = std::distance( std::lower_bound( x.begin(), x.end(), *xIter ), x.end() ) - 1;
        x.erase( std::prev( x.end(), offset ), x.end() );
        y.erase( std::prev( y.end(), offset ), y.end() );
      }

      bool linearised = std::all_of( interpolants.begin(), interpolants.end(),
                                     [] ( auto&& type )
                                        { return type == interpolation::InterpolationType::LinearLinear; } );

      return { std::move( x ), std::move( y ),
               std::move( boundaries ), std::move( interpolants ),
               linearised, curated };
    }

    static ProcessedData
    processData( std::vector< X >&& x, std::vector< Y >&& y,
                 interpolation::InterpolationType interpolant,
                 bool curate = false ) {

      return processData( std::move( x ), std::move( y ),
                          { x.size() > 0 ? x.size() - 1 : 0 },
                          { interpolant }, curate );
    }

    /**
     *  @brief Return the interpolation tables
     */
    const std::vector< TableVariant >& tables() const noexcept {

      return this->tables_;
    }

    /* interface implementation functions */

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      std::size_t index = 0;

      if ( this->numberRegions() > 1 ) {

        // look in the grid for the x value
        // upper_bound is used to get above jumps in the grid
        auto xIter = std::upper_bound( this->x().begin(),
                                       this->x().end(), x );
        index = std::distance( this->x().begin(), xIter );

        // get the table that has to interpolate on this value
        auto bIter = std::lower_bound( this->boundaries().begin(),
                                       this->boundaries().end(), index );
        if ( this->boundaries().end() == bIter ) {

          --bIter;
        }
        index = std::distance( this->boundaries().begin(), bIter );
      }

      return std::visit( [&x] ( const auto& table )
                              { return table.evaluate( x ); },
                         this->tables()[index] );
    }

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param data   the processed tabulated data
     */
    InterpolationTable( ProcessedData&& data ) :
      Parent( IntervalDomain( data.x.front(), data.x.back() ) ),
      x_( std::move( data.x ) ),
      y_( std::move( data.y ) ),
      boundaries_( std::move( data.boundaries ) ),
      interpolants_( std::move( data.interpolants ) ),
      linearised_( data.linearised ),
      curated_( data.curated ) {

      this->generateTables();
    }

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    InterpolationTable() = default;

    /**
     *  @brief Copy constructor
     *
     *  @param[in] table    the table to be copied
     */
    InterpolationTable( const InterpolationTable& table ) :
      Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
      x_( table.x_ ),
      y_( table.y_ ),
      boundaries_( table.boundaries_ ),
      interpolants_( table.interpolants_ ),
      linearised_( table.linearised_ ),
      curated_( table.curated_ ) {

      this->generateTables();
    }

    /**
     *  @brief Move constructor
     *
     *  @param[in] table    the table to be moved
     */
    InterpolationTable( InterpolationTable&& table ) :
      Parent( IntervalDomain( table.x_.front(), table.x_.back() ) ),
      x_( std::move( table.x_ ) ),
      y_( std::move( table.y_ ) ),
      boundaries_( std::move( table.boundaries_ ) ),
      interpolants_( std::move( table.interpolants_ ) ),
      linearised_( table.linearised_ ),
      curated_( table.curated_ ) {

      this->generateTables();
    }

    /**
     *  @brief Copy assignment using a continuous energy table
     *
     *  @param[in] table    the continuous energy table to be copied
     */
    InterpolationTable& operator=( const InterpolationTable& base ) {

      if ( this != &base ) {

        Parent::operator=( base );
        this->x_ = base.x_;
        this->y_ = base.y_;
        this->boundaries_ = base.boundaries_;
        this->interpolants_ = base.interpolants_;
        this->linearised_ = base.linearised_;
        this->curated_ = base.curated_;
        this->generateTables();
      }
      return *this;
    }

    /**
     *  @brief Move assignment using a continuous energy table
     *
     *  @param[in] table    the continuous energy table to be moved
     */
    InterpolationTable& operator=( InterpolationTable&& base ) {

      if ( this != &base ) {

        Parent::operator=( std::move( base ) );
        this->x_ = std::move( base.x_ );
        this->y_ = std::move( base.y_ );
        this->boundaries_ = std::move( base.boundaries_ );
        this->interpolants_ = std::move( base.interpolants_ );
        this->linearised_ = base.linearised_;
        this->curated_ = base.curated_;
        this->generateTables();
      }
      return *this;
    }

    /**
     *  @brief Constructor
     *
     *  @param x              the x values of the tabulated data
     *  @param y              the y values of the tabulated data
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     *  @param curate         flag to indicate whether or not to curate the table (default: false)
     */
    InterpolationTable( std::vector< X > x, std::vector< Y > y,
                        std::vector< std::size_t > boundaries,
                        std::vector< interpolation::InterpolationType > interpolants,
                        bool curate = false ) :
      InterpolationTable( processData( std::move( x ), std::move( y ),
                                             std::move( boundaries ),
                                             std::move( interpolants ), curate ) ) {}

    /**
     *  @brief Constructor for tabulated data in a single interpolation zone
     *
     *  @param x              the x values of the tabulated data
     *  @param y              the y values of the tabulated data
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     *  @param curate         flag to indicate whether or not to curate the table (default: false)
     */
    InterpolationTable( std::vector< X > x, std::vector< Y > y,
                        interpolation::InterpolationType interpolant =
                            interpolation::InterpolationType::LinearLinear,
                        bool curate = false ) :
      InterpolationTable( processData( std::move( x ), std::move( y ), interpolant, curate ) ) {}

    /* methods */

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< X >& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the y values of the table
     */
    const std::vector< Y >& y() const noexcept {

      return this->y_;
    }

    /**
     *  @brief Return the boundaries of the interpolation regions
     */
    const std::vector< std::size_t >& boundaries() const noexcept {

      return this->boundaries_;
    }

    /**
     *  @brief Return the interpolation types of the interpolation regions
     */
    const std::vector< interpolation::InterpolationType >& interpolants() const noexcept {

      return this->interpolants_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    /**
     *  @brief Return the number of interpolation regions in the table
     */
    std::size_t numberRegions() const noexcept {

      return this->boundaries().size();
    }

    /**
     *  @brief Return whether or not the data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    /**
     *  @brief Return whether or not the data is curated
     */
    bool isCurated() const noexcept {

      return this->curated_;
    }

    /**
     *  @brief Curate the table
     *
     *  This removes extraneous interior points in discontinuities in the data.
     */
    void curate() {

      if ( ! this->isCurated() ) {

        curateTable( this->x_, this->y_, this->boundaries_, this->interpolants_ );
        this->curated_ = true;
        this->generateTables();
      }
    }

    /**
     *  @brief Linearise the table and return a new InterpolationTable
     *
     *  If the table is already linearised and curated, a copy of the table is returned.
     *  Otherwise, the tabulated data of each region is stitched back together and a new table
     *  is reconstructed. Since the underlying views ensure unique x grids in each view,
     *  stitching the table back together will remove the extraneous points.
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    InterpolationTable linearise( Convergence&& convergence = Convergence() ) const {

      if ( ! ( this->isLinearised() && this->isCurated() ) ) {

        std::vector< X > x;
        std::vector< Y > y;
        std::vector< std::size_t > boundaries;
        std::vector< interpolation::InterpolationType > interpolants;

        auto linearise = [&convergence] ( const auto& table )
                                        { return table.linearise( convergence ); };

        auto check = [this] ( const auto& table ) {

          if ( table.x().end() == this->x().end() ) {

            // end of table
            return true;
          }
          else if ( *( table.x().end() ) != table.x().back() ) {

            // no jump
            return false;
          }
          else {

            // this is a jump: move to the last point
            auto xNext = std::prev( std::upper_bound( table.x().end(), this->x().end(),
                                                      table.x().back() ) );
            auto yNext = std::next( table.y().end(), std::distance( table.x().end(), xNext ) );
            return *yNext != table.y().back();
          }
        };

        for ( const auto& table : this->tables_ ) {

          auto linearised = std::visit( linearise, table );
          bool isJumpOrEnd = std::visit( check, table );

          if ( isJumpOrEnd ) {

            x.insert( x.end(), linearised.first.begin(), linearised.first.end() );
            y.insert( y.end(), linearised.second.begin(), linearised.second.end() );
            boundaries.push_back( x.size() - 1 );
            interpolants.push_back( interpolation::InterpolationType::LinearLinear );
          }
          else {

            x.insert( x.end(), linearised.first.begin(), std::prev( linearised.first.end() ) );
            y.insert( y.end(), linearised.second.begin(), std::prev( linearised.second.end() ) );
          }
        }

        return InterpolationTable( std::move( x ), std::move( y ),
                                   std::move( boundaries ), std::move( interpolants ) );
      }
      else {

        return *this;
      }
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator+=( const Y& right ) {

      return this->operationForLinearisedOnly( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator-=( const Y& right ) {

      return this->operationForLinearisedOnly( right, std::minus< Y >() );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable& operator*=( const S& right ) {

      return this->operation( right, std::multiplies< Y >() );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable& operator/=( const S& right ) {

      return this->operation( right, std::divides< Y >() );
    }

    /**
     *  @brief InterpolationTable and scalar addition
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator+( const Y& right ) const {

      InterpolationTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator-( const Y& right ) const {

      InterpolationTable result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable operator*( const S& right ) const {

      InterpolationTable result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable operator/( const S& right ) const {

      InterpolationTable result = *this;
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    InterpolationTable operator-() const {

      InterpolationTable result = *this;
      result *= -1;
      return result;
    }

    /**
     *  @brief Inplace InterpolationTable addition
     *
     *  @param[in] right    the table
     */
    InterpolationTable& operator+=( const InterpolationTable& right ) {

      return this->operation( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace InterpolationTable subtraction
     *
     *  @param[in] right    the table
     */
    InterpolationTable& operator-=( const InterpolationTable& right ) {

      return this->operation( right, std::minus< Y >() );
    }

    /**
     *  @brief InterpolationTable and InterpolationTable addition
     *
     *  @param[in] right    the table
     */
    InterpolationTable operator+( const InterpolationTable& right ) const {

      InterpolationTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief InterpolationTable and InterpolationTable subtraction
     *
     *  @param[in] right    the table
     */
    InterpolationTable operator-( const InterpolationTable& right ) const {

      InterpolationTable result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator==( const InterpolationTable& right ) const noexcept {

      return std::tie( this->interpolants(), this->boundaries(), this->x(), this->y() ) ==
             std::tie( right.interpolants(), right.boundaries(), right.x(), right.y() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator!=( const InterpolationTable& right ) const noexcept {

      return ! this->operator==( right );
    }

    using Parent::domain;
    using Parent::operator();

    /**
     *  @brief Calculate the integral of w(x) * f(x) dx over the table domain
     *
     *  The weight function must implement the math::WeightFunctionBase interface.
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) integrate( const WeightFunction& weight ) const {

      auto integrate = [&] ( auto&& region ) -> decltype(auto) {

        return region.integrate( weight );
      };

      auto compute = [&] ( auto&& result, auto&& variant ) -> decltype(auto) {

        return result + std::visit( integrate, variant );
      };

      auto iter = this->tables().begin();
      auto result = std::visit( integrate, *iter );
      ++iter;

      return std::accumulate( iter, this->tables().end(), result, compute );
    }

    /**
     *  @brief Calculate the integral over the table domain
     */
    decltype(auto) integral() const {

      return this->integrate( ConstantWeightFunction< X, double >{ 1. } );
    }

    /**
     *  @brief Calculate the cumulative integral of w(x) * f(x) dx over the table domain
     *
     *  The weight function must implement the math::WeightFunctionBase interface.
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) cumulativeIntegrate( const WeightFunction& weight ) const {

      using I = decltype( weight.integrateHistogram( this->x()[0], this->x()[1], this->y()[0], this->y()[1] ) );

      I first{ 0. };
      auto cumulative = [&] ( auto&& table ) {

        return table.cumulativeIntegrate( first, weight );
      };

      auto number_equal_x = [this] ( const auto& table ) {

        return std::distance( std::prev( table.x().end() ),
                              std::upper_bound( table.x().end(), this->x().end(),
                                                table.x().back() ) );
      };

      auto iter = this->tables().begin();
      auto result = std::visit( cumulative, *iter );
      ++iter;

      while ( iter != this->tables().end() ) {

        first = result.back();
        auto integrals = std::visit( cumulative, *iter );
        auto points = std::visit( number_equal_x, *std::prev( iter ) );

        if ( points > 1 ) {

          result.insert( result.end(), points - 1, first );
        }
        result.insert( result.end(), std::next( integrals.begin() ), integrals.end() );

        ++iter;
      }

      return result;
    }

    /**
     *  @brief Calculate the cumulative integral over the table domain
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > cumulativeIntegral() const {

      return this->cumulativeIntegrate( ConstantWeightFunction< X, double >{ 1. } );
    }

    /**
     *  @brief Calculate the mean over the table domain
     *
     *  Note: unnormalised and normalised tables return the same mean value.
     */
    X mean() const {

      return this->integrate( MeanWeightFunction< X >{} ) / this->integral();
    }

    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

  /**
   *  @brief Scalar and InterpolationTable addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  InterpolationTable< X, Y >
  operator+( const Y& left, const InterpolationTable< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and InterpolationTable subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  InterpolationTable< X, Y >
  operator-( const Y& left, const InterpolationTable< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and InterpolationTable multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  InterpolationTable< X, Y >
  operator*( const S& left, const InterpolationTable< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_MATH_INTERPOLATIONTABLEFUNCTION
#define NJOY_SCION_MATH_INTERPOLATIONTABLEFUNCTION

// system includes
#include <algorithm>
#include <tuple>
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "utility/IteratorView.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/math/ProcessedData.hpp"
#include "scion/math/TwoDimensionalFunctionBase.hpp"
#include "scion/math/HistogramTableFunction.hpp"
#include "scion/math/LinearLinearTableFunction.hpp"
#include "scion/math/LinearLogTableFunction.hpp"
#include "scion/math/LogLinearTableFunction.hpp"
#include "scion/math/LogLogTableFunction.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with one or more interpolation types
   */
  template < typename X, typename F >
  class InterpolationTableFunction :
      public TwoDimensionalFunctionBase< InterpolationTableFunction< X, F >,
                                         X, typename F::XType, typename F::YType > {

    /* friend declarations */

    friend class TwoDimensionalFunctionBase< InterpolationTableFunction< X, F >,
                                             X, typename F::XType, typename F::YType >;

    /* type aliases */

    using Parent = TwoDimensionalFunctionBase< InterpolationTableFunction< X, F >, X,
                                               typename F::XType, typename F::YType >;
    using Y = typename Parent::YType;
    using Z = typename Parent::ZType;
    using XIterator = typename std::vector< X >::const_iterator;
    using FIterator = typename std::vector< F >::const_iterator;
    using XContainer = njoy::utility::IteratorView< XIterator >;
    using FContainer = njoy::utility::IteratorView< FIterator >;
    using TableVariant = std::variant<
                             LinearLinearTableFunction< X, F, XContainer, FContainer >,
                             HistogramTableFunction< X, F, XContainer, FContainer >,
                             LinearLogTableFunction< X, F, XContainer, FContainer >,
                             LogLinearTableFunction< X, F, XContainer, FContainer >,
                             LogLogTableFunction< X, F, XContainer, FContainer > >;

    /* fields */

    std::vector< X > x_;
    std::vector< F > f_;
    std::vector< std::size_t > boundaries_;
    std::vector< interpolation::InterpolationType > interpolants_;
    bool curated_;

    std::vector< TableVariant > tables_;

    /* auxiliary function */

    void generateTables() {

      std::vector< TableVariant > tables;

      auto xStart = this->x().begin();
      auto fStart = this->f().begin();
      std::size_t nr = this->boundaries().size();
      for ( std::size_t i = 0; i < nr; ++i ) {

        auto xEnd = this->x().begin();
        auto fEnd = this->f().begin();
        std::advance( xEnd, this->boundaries()[i] + 1 );
        std::advance( fEnd, this->boundaries()[i] + 1 );

        switch ( this->interpolants()[i] ) {

          case interpolation::InterpolationType::LinearLinear : {

            tables.emplace_back(
              LinearLinearTableFunction< X, F, XContainer, FContainer >(
                XContainer( xStart, xEnd ),
                FContainer( fStart, fEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::Histogram : {

            tables.emplace_back(
              HistogramTableFunction< X, F, XContainer, FContainer >(
                XContainer( xStart, xEnd ),
                FContainer( fStart, fEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LinearLog : {

            tables.emplace_back(
              LinearLogTableFunction< X, F, XContainer, FContainer >(
                XContainer( xStart, xEnd ),
                FContainer( fStart, fEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LogLinear : {

            tables.emplace_back(
              LogLinearTableFunction< X, F, XContainer, FContainer >(
                XContainer( xStart, xEnd ),
                FContainer( fStart, fEnd ) ) );
            break;
          }
          case interpolation::InterpolationType::LogLog : {

            tables.emplace_back(
              LogLogTableFunction< X, F, XContainer, FContainer >(
                XContainer( xStart, xEnd ),
                FContainer( fStart, fEnd ) ) );
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
          std::swap( fStart, fEnd );
          if ( *xStart > *std::prev( xStart ) ) {

            --xStart;
            --fStart;
          }
          else {

            auto iter = std::prev( std::upper_bound( xStart, this->x().end(), *xStart ) );
            auto offset = std::distance( xStart, iter );
            std::advance( xStart, offset );
            std::advance( fStart, offset );
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
    static void curateTable( std::vector< X >& x, std::vector< F >& f,
                             std::vector< std::size_t >& boundaries,
                             std::vector< interpolation::InterpolationType >& /* interpolants */ ) {

      auto xRead = x.begin();
      auto fRead = f.begin();
      auto xWrite = x.begin();
      auto fWrite = f.begin();
      std::size_t removed = 0;
      for ( auto& boundary : boundaries ) {

        // the points up to and including the boundary point are kept
        auto xEnd = std::next( x.begin(), boundary + 1 );
        auto fEnd = std::next( f.begin(), boundary + 1 );

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
          fWrite = std::move( fRead, fEnd, fWrite );
        }
        else {

          xWrite = xEnd;
          fWrite = fEnd;
        }
        xRead = std::next( xEnd, extraneous );
        fRead = std::next( fEnd, extraneous );

        boundary -= removed;
        removed += extraneous;
      }

      x.erase( xWrite, x.end() );
      f.erase( fWrite, f.end() );
    }

    /**
     *  @brief Verify and correct boundaries and interpolants
     *
     *  This function does a lot, so here's an overview of what it does. First of all, it verifies
     *  the following things:
     *    - There are at least 2 values in the x and f(y) grid
     *    - The x and f(y) grid have the same size
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
    static ProcessedData< X, F >
    processData( std::vector< X >&& x, std::vector< F >&& f,
                 std::vector< std::size_t >&& boundaries,
                 std::vector< interpolation::InterpolationType >&& interpolants,
                 bool curate = false ) {

      if ( ( ! verification::isAtLeastOfSize( x, 2 ) ) ||
           ( ! verification::isAtLeastOfSize( f, 2 ) ) ) {

        Log::error( "Insufficient x values or f(y) functions defined for tabulated data "
                    "(at least 2 points are required)" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "f.size(): {}", f.size() );
        throw std::exception();
      }

      if ( ! verification::isSameSize( x, f ) ) {

        Log::error( "Inconsistent number of x values and f(y) functions for tabulated data" );
        Log::info( "x.size(): {}", x.size() );
        Log::info( "f.size(): {}", f.size() );
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

        curateTable( x, f, boundaries, interpolants );
        curated = true;
      }

      // check for a jump at the beginning of the table (all but the last point are removed)
      xIter = x.begin();
      if ( *xIter == *( std::next( xIter ) ) ) {

        Log::warning( "A jump at the beginning of the table (x = {}) has been removed", *xIter );
        auto offset = std::distance( x.begin(), std::upper_bound( x.begin(), x.end(), *xIter ) ) - 1;
        x.erase( x.begin(), std::next( x.begin(), offset ) );
        f.erase( f.begin(), std::next( f.begin(), offset ) );
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
        f.erase( std::prev( f.end(), offset ), f.end() );
      }

      return { std::move( x ), std::move( f ),
               std::move( boundaries ), std::move( interpolants ),
               false, curated };
    }

    static ProcessedData< X, F >
    processData( std::vector< X >&& x, std::vector< F >&& f,
                 interpolation::InterpolationType interpolant,
                 bool curate = false ) {

      return processData( std::move( x ), std::move( f ),
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
     *  @brief Evaluate the function for a value of x and y
     *
     *  @param x   the x value to be evaluated
     *  @param y   the y value to be evaluated
     */
    Z evaluate( const X& x, const Y& y ) const {

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

      return std::visit( [&x, &y] ( const auto& table )
                                  { return table.evaluate( x, y ); },
                         this->tables()[index] );
    }

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param data   the processed tabulated data
     */
    InterpolationTableFunction( ProcessedData< X, F >&& data ) :
      x_( std::move( data.x ) ),
      f_( std::move( data.y ) ),
      boundaries_( std::move( data.boundaries ) ),
      interpolants_( std::move( data.interpolants ) ),
      curated_( data.curated ) {

      this->generateTables();
    }

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::ZType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    InterpolationTableFunction() = default;

    /**
     *  @brief Copy constructor
     *
     *  @param[in] table    the table to be copied
     */
    InterpolationTableFunction( const InterpolationTableFunction& table ) :
      x_( table.x_ ),
      f_( table.f_ ),
      boundaries_( table.boundaries_ ),
      interpolants_( table.interpolants_ ),
      curated_( table.curated_ ) {

      this->generateTables();
    }

    /**
     *  @brief Move constructor
     *
     *  @param[in] table    the table to be moved
     */
    InterpolationTableFunction( InterpolationTableFunction&& table ) :
      x_( std::move( table.x_ ) ),
      f_( std::move( table.f_ ) ),
      boundaries_( std::move( table.boundaries_ ) ),
      interpolants_( std::move( table.interpolants_ ) ),
      curated_( table.curated_ ) {

      this->generateTables();
    }

    /**
     *  @brief Copy assignment using a table
     *
     *  @param[in] table    the table to be copied
     */
    InterpolationTableFunction& operator=( const InterpolationTableFunction& base ) {

      if ( this != &base ) {

        Parent::operator=( base );
        this->x_ = base.x_;
        this->f_ = base.f_;
        this->boundaries_ = base.boundaries_;
        this->interpolants_ = base.interpolants_;
        this->curated_ = base.curated_;
        this->generateTables();
      }
      return *this;
    }

    /**
     *  @brief Move assignment using a table
     *
     *  @param[in] table    the table to be moved
     */
    InterpolationTableFunction& operator=( InterpolationTableFunction&& base ) {

      if ( this != &base ) {

        Parent::operator=( base );
        this->x_ = std::move( base.x_ );
        this->f_ = std::move( base.f_ );
        this->boundaries_ = std::move( base.boundaries_ );
        this->interpolants_ = std::move( base.interpolants_ );
        this->curated_ = base.curated_;
        this->generateTables();
      }
      return *this;
    }

    /**
     *  @brief Constructor
     *
     *  @param x              the x values of the tabulated data
     *  @param f              the f(y) functions of the tabulated data
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     *  @param curate         flag to indicate whether or not to curate the table (default: false)
     */
    InterpolationTableFunction( std::vector< X > x, std::vector< F > f,
                                std::vector< std::size_t > boundaries,
                                std::vector< interpolation::InterpolationType > interpolants,
                                bool curate = false ) :
      InterpolationTableFunction( processData( std::move( x ), std::move( f ),
                                               std::move( boundaries ),
                                               std::move( interpolants ), curate ) ) {}

    /**
     *  @brief Constructor for tabulated data in a single interpolation zone
     *
     *  @param x              the x values of the tabulated data
     *  @param f              the f(y) functions of the tabulated data
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     *  @param curate         flag to indicate whether or not to curate the table (default: false)
     */
    InterpolationTableFunction( std::vector< X > x, std::vector< F > f,
                                interpolation::InterpolationType interpolant =
                                    interpolation::InterpolationType::LinearLinear,
                                bool curate = false ) :
      InterpolationTableFunction( processData( std::move( x ), std::move( f ), interpolant, curate ) ) {}

    /* methods */

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< X >& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the x values of the table
     *
     *  DO NOT USE THIS TO ADD/REMOVE ELEMENTS OR YOU WILL BREAK THINGS!
     */
    std::vector< X >& x() noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the f(y) functions of the table
     */
    const std::vector< F >& f() const noexcept {

      return this->f_;
    }

    /**
     *  @brief Return the f(y) functions of the table
     *
     *  DO NOT USE THIS TO ADD/REMOVE ELEMENTS OR YOU WILL BREAK THINGS!
     */
    std::vector< F >& f() noexcept {

      return this->f_;
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
     *  @brief Return whether or not the data is curated
     *
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

        curateTable( this->x_, this->f_, this->boundaries_, this->interpolants_ );
        this->curated_ = true;
        this->generateTables();
      }
    }

    using Parent::operator();

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator==( const InterpolationTableFunction& right ) const noexcept {

      return std::tie( this->interpolants(), this->boundaries(), this->x(), this->f() ) ==
             std::tie( right.interpolants(), right.boundaries(), right.x(), right.f() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator!=( const InterpolationTableFunction& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

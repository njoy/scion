#ifndef NJOY_SCION_MATH_LOGLOGTABLE
#define NJOY_SCION_MATH_LOGLOGTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/LogarithmicLogarithmic.hpp"
#include "scion/interpolation/Table.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/math/LinearLinearTable.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with log-log interpolation
   */
  template < typename X, typename Y = X >
  class LogLogTable : public FunctionBase< LogLogTable< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< LogLogTable< X, Y >, X, Y >;
    using Table = interpolation::Table< interpolation::LogarithmicLogarithmic,
                                        std::vector< X >,
                                        std::vector< Y > >;

    /* fields */
    Table table_;

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LogLogTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< X >& x() const noexcept {

      return this->table_.x();
    }

    /**
     *  @brief Return the y values of the table
     */
    const std::vector< Y >& y() const noexcept {

      return this->table_.y();
    }

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return this->table_.evaluate( x );
    }

    /**
     *  @brief Linearise the table and return a LinearLinearTable
     *
     *  Note: this function returns a copy of the original table.
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    LinearLinearTable< X, Y > linearise( Convergence&& convergence = Convergence() ) const {

      std::vector< X > x;
      std::vector< Y > y;
      linearisation::Lineariser lineariser( x, y );
      lineariser( this->x(),
                  *this,
                  std::forward< Convergence >( convergence ),
                  linearisation::MidpointSplit< X >() );

      return LinearLinearTable< X, Y >( std::move( x ), std::move( y ) );
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

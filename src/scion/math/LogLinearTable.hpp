#ifndef NJOY_SCION_MATH_LOGLINEARTABLE
#define NJOY_SCION_MATH_LOGLINEARTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/LogarithmicLinear.hpp"
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
  class LogLinearTable : public FunctionBase< LogLinearTable< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< LogLinearTable< X, Y >, X, Y >;
    using Table = interpolation::Table< interpolation::LogarithmicLinear,
                                        std::vector< X >,
                                        std::vector< Y > >;

    /* fields */
    Table table_;

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LogLinearTable/src/ctor.hpp"

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

    #include "scion/math/LogLinearTable/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

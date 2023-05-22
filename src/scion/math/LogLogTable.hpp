#ifndef NJOY_SCION_MATH_LOGLOGTABLE
#define NJOY_SCION_MATH_LOGLOGTABLE

// system includes
#include <vector>

// other includes
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/interpolation/InterpolationType.hpp"
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
   *  @brief Tabulated data with log-log interpolation (ln(y) is linear in ln(x))
   */
  template < typename X, typename Y = X,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LogLogTable :
    public FunctionBase< LogLogTable< X, Y, XContainer, YContainer >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< LogLogTable< X, Y, XContainer, YContainer >, X, Y >;
    using Table = interpolation::Table< interpolation::LogarithmicLogarithmic,
                                        XContainer, YContainer >;

    /* fields */
    Table table_;

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LogLogTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType interpolation() noexcept {

      return interpolation::InterpolationType::LogLog;
    }

    /**
     *  @brief Return the x values of the table
     */
    const YContainer& x() const noexcept {

      return this->table_.x();
    }

    /**
     *  @brief Return the y values of the table
     */
    const YContainer& y() const noexcept {

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

    #include "scion/math/LogLogTable/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

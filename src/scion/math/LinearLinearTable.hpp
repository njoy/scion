#ifndef NJOY_SCION_MATH_LINEARLINEARTABLE
#define NJOY_SCION_MATH_LINEARLINEARTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/interpolation/Table.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/FunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with linear-linear interpolation (y is linear in x)
   */
  template < typename X, typename Y = X >
  class LinearLinearTable : public FunctionBase< LinearLinearTable< X, Y >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< LinearLinearTable< X, Y >, X, Y >;
    using Table = interpolation::Table< interpolation::LinearLinear,
                                        std::vector< X >,
                                        std::vector< Y > >;

    /* fields */
    Table table_;

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LinearLinearTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType interpolation() noexcept {

      return interpolation::InterpolationType::LinearLinear;
    }

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
    LinearLinearTable linearise( Convergence&& = Convergence() ) const {

      return *this;
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

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
   *
   *  The LinearLinearTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y = X,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LinearLinearTable :
    public FunctionBase< LinearLinearTable< X, Y, XContainer, YContainer >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< LinearLinearTable< X, Y, XContainer, YContainer >, X, Y >;
    using Table = interpolation::Table< interpolation::LinearLinear,
                                        XContainer, YContainer >;

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
    const XContainer& x() const noexcept {

      return this->table_.x();
    }

    /**
     *  @brief Return the y values of the table
     */
    const YContainer& y() const noexcept {

      return this->table_.y();
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
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
    LinearLinearTable< X, Y > linearise( Convergence&& = Convergence() ) const {

      return { std::vector< X >{ this->x().begin(), this->x().end() },
               std::vector< Y >{ this->y().begin(), this->y().end() } };
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

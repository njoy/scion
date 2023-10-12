#ifndef NJOY_SCION_MATH_SINGLETABLEBASE
#define NJOY_SCION_MATH_SINGLETABLEBASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/Table.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for tabulated data using a single interpolation region
   *
   *  This base class provides the common interface for single region
   *  interpolation data such as the LinearLinearTable, LogLogTable, etc.
   */
  template < typename Derived, typename Interpolator,
             typename X, typename Y = X,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class SingleTableBase : public FunctionBase< Derived, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< Derived, X, Y >;
    using Table = interpolation::Table< Interpolator,
                                        XContainer, YContainer >;

  public:

    /* type aliases */
    using DomainVariant = typename Parent::DomainVariant;

  private:

    /* fields */
    Table table_;

    /* auxiliary function */
    #include "scion/math/SingleTableBase/src/verifyTable.hpp"

  protected:

    /* constructor */
    #include "scion/math/SingleTableBase/src/ctor.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    constexpr interpolation::InterpolationType interpolation() const noexcept {

      return static_cast< const Derived* >( this )->type();
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

    #include "scion/math/SingleTableBase/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

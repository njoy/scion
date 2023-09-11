#ifndef NJOY_SCION_MATH_HISTOGRAMTABLE
#define NJOY_SCION_MATH_HISTOGRAMTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/Histogram.hpp"
#include "scion/interpolation/Table.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with histogram interpolation (y is constant in x)
   *
   *  The HistogramTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y = X,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class HistogramTable :
    public FunctionBase< HistogramTable< X, Y, XContainer, YContainer >, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< HistogramTable< X, Y, XContainer, YContainer >, X, Y >;
    using Table = interpolation::Table< interpolation::Histogram,
                                        XContainer, YContainer >;

    /* fields */
    Table table_;

    /* auxiliary function */
    #include "scion/math/HistogramTable/src/verifyTable.hpp"

  public:

    /* constructor */
    #include "scion/math/HistogramTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType interpolation() noexcept {

      return interpolation::InterpolationType::Histogram;
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
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y evaluate( const X& x ) const {

      return this->table_.evaluate( x );
    }

    #include "scion/math/HistogramTable/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

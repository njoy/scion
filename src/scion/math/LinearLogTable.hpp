#ifndef NJOY_SCION_MATH_LINEARLOGTABLE
#define NJOY_SCION_MATH_LINEARLOGTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LinearLogarithmic.hpp"
#include "scion/math/SingleTableBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with linear-log interpolation (y is linear in ln(x))
   *
   *  The LinearLogTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y = X,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LinearLogTable :
    public SingleTableBase< LinearLogTable< X, Y, XContainer, YContainer >,
                            interpolation::LinearLogarithmic, X, Y,
                            XContainer, YContainer > {

    /* type aliases */
    using Parent = SingleTableBase< LinearLogTable< X, Y, XContainer, YContainer >,
                                    interpolation::LinearLogarithmic, X, Y,
                                    XContainer, YContainer >;

    /* fields */

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LinearLogTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LinearLog;
    }

    using Parent::interpolation;
    using Parent::x;
    using Parent::y;
    using Parent::numberPoints;
    using Parent::linearise;
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

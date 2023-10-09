#ifndef NJOY_SCION_MATH_LINEARLINEARTABLE
#define NJOY_SCION_MATH_LINEARLINEARTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableBase.hpp"

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
    public SingleTableBase< LinearLinearTable< X, Y, XContainer, YContainer >,
                            interpolation::LinearLinear, X, Y,
                            XContainer, YContainer > {

    /* type aliases */
    using Parent = SingleTableBase< LinearLinearTable< X, Y, XContainer, YContainer >,
                                    interpolation::LinearLinear, X, Y,
                                    XContainer, YContainer >;

    /* fields */

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/math/LinearLinearTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LinearLinear;
    }

    using Parent::interpolation;
    using Parent::x;
    using Parent::y;
    using Parent::numberPoints;

    /**
     *  @brief Linearise the table and return a LinearLinearTable
     *
     *  Note: this function returns a copy of the original table.
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    std::pair< std::vector< X >, std::vector< X > >
    linearise( Convergence&& = Convergence() ) const {

      return { std::vector< X >{ this->x().begin(), this->x().end() },
               std::vector< Y >{ this->y().begin(), this->y().end() } };
    }

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

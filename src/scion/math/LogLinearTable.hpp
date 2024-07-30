#ifndef NJOY_SCION_MATH_LOGLINEARTABLE
#define NJOY_SCION_MATH_LOGLINEARTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/math/SingleTableBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,y data with log-linear interpolation (ln(y) is linear in x)
   *
   *  The LogLinearTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LogLinearTable :
    public SingleTableBase< LogLinearTable< X, Y, XContainer, YContainer >,
                            interpolation::LogarithmicLinear, X, Y,
                            XContainer, YContainer > {

    /* friend declarations */
    friend class SingleTableBase< LogLinearTable< X, Y, XContainer, YContainer >,
                                  interpolation::LogarithmicLinear, X, Y,
                                  XContainer, YContainer >;

    /* type aliases */
    using Parent = SingleTableBase< LogLinearTable< X, Y, XContainer, YContainer >,
                                    interpolation::LogarithmicLinear, X, Y,
                                    XContainer, YContainer >;

    /* fields */

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LogLinear;
    }

  public:

    /* constructor */
    #include "scion/math/LogLinearTable/src/ctor.hpp"

    /* methods */

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

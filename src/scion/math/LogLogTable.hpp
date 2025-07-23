#ifndef NJOY_SCION_MATH_LOGLOGTABLE
#define NJOY_SCION_MATH_LOGLOGTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"
#include "scion/integration/LogarithmicLogarithmic.hpp"
#include "scion/integration/LogarithmicLogarithmicMean.hpp"
#include "scion/math/SingleTableBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,y data with log-log interpolation (ln(y) is linear in ln(x))
   *
   *  The LogLogTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LogLogTable :
    public SingleTableBase< LogLogTable< X, Y, XContainer, YContainer >,
                            X, Y, XContainer, YContainer > {

    /* friend declarations */
    friend class SingleTableBase< LogLogTable< X, Y, XContainer, YContainer >,
                                  X, Y, XContainer, YContainer >;

    /* type aliases */
    using Parent = SingleTableBase< LogLogTable< X, Y, XContainer, YContainer >,
                                    X, Y, XContainer, YContainer >;

    /* fields */

    /* auxiliary functions */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LogLog;
    }

    /**
     *  @brief Interpolate
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    static constexpr Y interpolate( const X& x,
                                    const X& xLeft, const X& xRight,
                                    const Y& yLeft, const Y& yRight ) noexcept {

      return interpolation::loglog( x, xLeft, xRight, yLeft, yRight );
    }

  public:

    /* constructor */
    #include "scion/math/LogLogTable/src/ctor.hpp"

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

    /**
     *  @brief Calculate the integral (zeroth order moment) of the table over its domain
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    I integral() const {

      return Parent::integral( integration::loglog );
    }

    /**
     *  @brief Calculate the mean (first order raw moment) of the table over its domain
     */
    template < typename I = decltype( std::declval< X >() * std::declval< X >() * std::declval< Y >() ) >
    I mean() const {

      return Parent::integral( integration::logLogMean );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_MATH_HISTOGRAMTABLE
#define NJOY_SCION_MATH_HISTOGRAMTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/Histogram.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,y data with histogram interpolation (y is constant in x)
   *
   *  The HistogramTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class HistogramTable :
    public SingleTableBase< HistogramTable< X, Y, XContainer, YContainer >,
                            interpolation::Histogram, X, Y,
                            XContainer, YContainer > {

    /* friend declarations */
    friend class SingleTableBase< HistogramTable< X, Y, XContainer, YContainer >,
                                  interpolation::Histogram, X, Y,
                                  XContainer, YContainer >;

    /* type aliases */
    using Parent = SingleTableBase< HistogramTable< X, Y, XContainer, YContainer >,
                                    interpolation::Histogram, X, Y,
                                    XContainer, YContainer >;

    /* fields */

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::Histogram;
    }

  public:

    /* constructor */
    #include "scion/math/HistogramTable/src/ctor.hpp"

    /* methods */

    using Parent::interpolation;
    using Parent::x;
    using Parent::y;
    using Parent::numberPoints;

    #include "scion/math/HistogramTable/src/linearise.hpp"

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

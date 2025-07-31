#ifndef NJOY_SCION_MATH_SINGLETABLEBASE
#define NJOY_SCION_MATH_SINGLETABLEBASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/integration/integral.hpp"
#include "scion/integration/cumulativeIntegral.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for x,y tabulated data using a single interpolation region
   *
   *  This base class provides the common interface for single region
   *  interpolation data such as the LinearLinearTable, LogLogTable, etc.
   */
  template < typename Derived, typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class SingleTableBase : public OneDimensionalFunctionBase< Derived, X, Y > {

    /* type aliases */
    using Parent = OneDimensionalFunctionBase< Derived, X, Y >;

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

  private:

    /* fields */
    XContainer x_;
    YContainer y_;

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

      return this->x_;
    }

    /**
     *  @brief Return the y values of the table
     */
    const YContainer& y() const noexcept {

      return this->y_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    #include "scion/math/SingleTableBase/src/evaluate.hpp"
    #include "scion/math/SingleTableBase/src/linearise.hpp"

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;

    /**
     *  @brief Calculate the integral by applying an analytical integrator
     *         over each panel in the table
     *
     *  @param[in] integrator   the integrator to be applied
     */
    template < typename Integrator >
    auto integral( const Integrator& integrator ) const {

      return integration::integral( this->x(), this->y(), integrator );
    }

    /**
     *  @brief Calculate the cumulative integral by applying an analytical integrator
     *         over each panel in the table
     *
     *  @param[in] initial      the initial value of the cumulative integral to be used
     *                          (i.e. the value of the integral at the end of the previous
     *                          interpolation zone or zero if this is the first region)
     *  @param[in] integrator   the integrator to be applied
     */
    template < typename I, typename Integrator >
    auto cumulativeIntegral( const I& initial, const Integrator& integrator ) const {

      return integration::cumulativeIntegral( initial, this->x(), this->y(), integrator );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

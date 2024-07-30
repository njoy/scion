#ifndef NJOY_SCION_MATH_SINGLETABLEFUNCTIONBASE
#define NJOY_SCION_MATH_SINGLETABLEFUNCTIONBASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/math/TwoDimensionalFunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for x,f(y) tabulated data using a single interpolation region
   */
  template < typename Derived, typename Interpolator,
             typename X, typename Y, typename Z, typename F,
             typename XContainer = std::vector< X >,
             typename FContainer = std::vector< F > >
  class SingleTableFunctionBase : public TwoDimensionalFunctionBase< Derived, X, Y, Z > {

    /* type aliases */
    using Parent = TwoDimensionalFunctionBase< Derived, X, Y, Z >;

    /* fields */
    Interpolator interpolator_;
    XContainer x_;
    FContainer f_;

    /* auxiliary function */
    #include "scion/math/SingleTableFunctionBase/src/verifyTable.hpp"

    /**
     *  @brief Return the panel interpolator
     */
    const Interpolator& interpolator() const noexcept {

      return this->interpolator_;
    }

  protected:

    /* constructor */
    #include "scion/math/SingleTableFunctionBase/src/ctor.hpp"

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
     *  @brief Return the f(y) functions of the table
     */
    const FContainer& f() const noexcept {

      return this->f_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    #include "scion/math/SingleTableFunctionBase/src/evaluate.hpp"

    using Parent::operator();
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif
#ifndef NJOY_SCION_MATH_LINEARLINEARTABLEFUNCTION
#define NJOY_SCION_MATH_LINEARLINEARTABLEFUNCTION

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableFunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,f(y) data with linear-linear interpolation (f(y) is linear in x)
   *
   *  The LinearLinearTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y, typename Z, typename F,
             typename XContainer = std::vector< X >,
             typename FContainer = std::vector< F > >
  class LinearLinearTableFunction :
    public SingleTableFunctionBase< LinearLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                    interpolation::LinearLinear, X, Y, Z, F,
                                    XContainer, FContainer > {

    /* friend declarations */
    friend class SingleTableFunctionBase< LinearLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                          interpolation::LinearLinear, X, Y, Z, F,
                                          XContainer, FContainer >;

    /* type aliases */
    using Parent = SingleTableFunctionBase< LinearLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                            interpolation::LinearLinear, X, Y, Z, F,
                                            XContainer, FContainer >;

    /* fields */

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LinearLinear;
    }

  public:

    /* constructor */
    #include "scion/math/LinearLinearTableFunction/src/ctor.hpp"

    /* methods */

    using Parent::interpolation;
    using Parent::x;
    using Parent::f;
    using Parent::numberPoints;
    using Parent::operator();
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

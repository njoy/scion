#ifndef NJOY_SCION_MATH_LOGLINEARTABLEFUNCTION
#define NJOY_SCION_MATH_LOGLINEARTABLEFUNCTION

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LogarithmicLinear.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableFunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,f(y) data with log-linear interpolation (ln(f(y)) is linear in x)
   *
   *  The LogLinearTableFunction is templatised on the actual x, y and z types, the function
   *  type F and the container type used for the x values and the functions. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y, typename Z, typename F,
             typename XContainer = std::vector< X >,
             typename FContainer = std::vector< F > >
  class LogLinearTableFunction :
    public SingleTableFunctionBase< LogLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                    interpolation::LogarithmicLinear, X, Y, Z, F,
                                    XContainer, FContainer > {

    /* friend declarations */
    friend class SingleTableFunctionBase< LogLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                          interpolation::LogarithmicLinear, X, Y, Z, F,
                                          XContainer, FContainer >;

    /* type aliases */
    using Parent = SingleTableFunctionBase< LogLinearTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                            interpolation::LogarithmicLinear, X, Y, Z, F,
                                            XContainer, FContainer >;

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
    #include "scion/math/LogLinearTableFunction/src/ctor.hpp"

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

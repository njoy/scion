#ifndef NJOY_SCION_MATH_LOGLOGTABLEFUNCTION
#define NJOY_SCION_MATH_LOGLOGTABLEFUNCTION

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LogarithmicLogarithmic.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableFunctionBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,f(y) data with log-log interpolation (ln(f(y)) is linear in ln(x))
   *
   *  The LogLogTableFunction is templatised on the actual x, y and z types, the function
   *  type F and the container type used for the x values and the functions. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y, typename Z, typename F,
             typename XContainer = std::vector< X >,
             typename FContainer = std::vector< F > >
  class LogLogTableFunction :
    public SingleTableFunctionBase< LogLogTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                    interpolation::LogarithmicLogarithmic, X, Y, Z, F,
                                    XContainer, FContainer > {

    /* friend declarations */
    friend class SingleTableFunctionBase< LogLogTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                          interpolation::LogarithmicLogarithmic, X, Y, Z, F,
                                          XContainer, FContainer >;

    /* type aliases */
    using Parent = SingleTableFunctionBase< LogLogTableFunction< X, Y, Z, F, XContainer, FContainer >,
                                            interpolation::LogarithmicLogarithmic, X, Y, Z, F,
                                            XContainer, FContainer >;

    /* fields */

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LogLog;
    }

  public:

    /* constructor */
    #include "scion/math/LogLogTableFunction/src/ctor.hpp"

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

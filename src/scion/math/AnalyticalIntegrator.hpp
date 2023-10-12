#ifndef NJOY_SCION_MATH_ANALYTICALINTEGRATOR
#define NJOY_SCION_MATH_ANALYTICALINTEGRATOR

// system includes

// other includes
#include "tools/Log.hpp"
#include "scion/math/InterpolationTable.hpp"
#include "scion/integration.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Analytical integration of data over a number of successive
   *         integration intervals
   */
  template < typename X >
  class AnalyticalIntegrator {

    /* friend declarations */

    /* fields */
    std::vector< X > boundaries_;

    /* auxiliary functions */
    #include "scion/math/AnalyticalIntegrator/src/verifyBoundaries.hpp"
    #include "scion/math/AnalyticalIntegrator/src/integrate.hpp"

  public:

    /* constructor */
    #include "scion/math/AnalyticalIntegrator/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the integration boundaries
     */
    const std::vector< X >& boundaries() const noexcept {

      return this->boundaries_;
    }

    /**
     *  @brief Return the number of integration intervals
     */
    unsigned int numberIntervals() const noexcept {

      return this->boundaries().size() - 1;
    }

    #include "scion/math/AnalyticalIntegrator/src/call.hpp"
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

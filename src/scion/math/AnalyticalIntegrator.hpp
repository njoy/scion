#ifndef NJOY_SCION_MATH_MULTIGROUPINTEGRATOR
#define NJOY_SCION_MATH_MULTIGROUPINTEGRATOR

// system includes

// other includes
#include "scion/math/InterpolationTable.hpp"
#include "scion/integration.hpp"
#include "utility/Log.hpp"

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

    /* auxiliary function */
    #include "scion/math/AnalyticalIntegrator/src/verifyBoundaries.hpp"

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

    #include "scion/math/AnalyticalIntegrator/src/integrate.hpp"
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTEGRATION_HISTOGRAM
#define NJOY_SCION_INTEGRATION_HISTOGRAM

// system includes

// other includes
#include "scion/integration/IntegratorBase.hpp"

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Histogram integration (y is constant in x)
   */
  class Histogram : public IntegratorBase< Histogram > {

    /* friend declarations */
    friend class IntegratorBase< Histogram >;

    /* interface implementation functions */

    /**
     *  @brief Perform histogram integration (y is constant in x)
     *
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    template < typename X, typename Y >
    Y integrate( const X& xLeft, const X& xRight,
                 const Y& yLeft, const Y& ) const noexcept {

      return yLeft * ( xRight - xLeft );
    }

  public:

    using IntegratorBase::operator();
  };

  // integration function
  static constexpr Histogram histogram;

} // interpolation namespace
} // scion namespace
} // njoy namespace

#endif

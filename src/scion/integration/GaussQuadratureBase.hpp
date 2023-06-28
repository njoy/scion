#ifndef NJOY_SCION_INTEGRATION_GAUSSQUADRATUREBASE
#define NJOY_SCION_INTEGRATION_GAUSSQUADRATUREBASE

// system includes
#include <algorithm>
#include <numeric>

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @class
   *  @brief Base class for Gauss quadrature rules
   *
   *  This base class provides the common interface for Gauss quadrature rules
   *  such as the Gauss-Legendre, Gauss-Lobatto and Curtis-Clenshaw rules.
   */
  template < typename Derived, typename X, typename Y = X >
  class GaussQuadratureBase {

    /* type aliases */
    using I = decltype( std::declval< X >() * std::declval< Y >() );

  public:

    /* methods */

    /**
     *  @brief Calculate the integral of a function over the interval [-1, 1]
     *
     *  @param[in] functor    the function to integrate
     */
    template < typename Functor >
    I operator()( Functor&& functor ) const {

      const auto accumulate = [&] ( auto&& result, auto&& pair ) {

        return std::move( result ) + pair.second * functor( pair.first );
      };

      return std::accumulate( Derived::pairs().cbegin(), Derived::pairs().cend(),
                              I( 0. ), accumulate );
    }
  };

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

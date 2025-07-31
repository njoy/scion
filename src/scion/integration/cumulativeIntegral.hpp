#ifndef NJOY_SCION_INTEGRATION_CUMULATIVE_INTEGRAL
#define NJOY_SCION_INTEGRATION_CUMULATIVE_INTEGRAL

// system includes
#include <vector>

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @brief Calculate the cumulative integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  @param[in]     initial      the initial value of the cumulative integral to be used
   *                              (i.e. the value of the integral at the end of the previous
   *                              interpolation zone or zero if this is the first region)
   *  @param[in,out] xbegin       the interator to the upper x value of the current interval
   *  @param[in]     xend         the interator to the end of the x values
   *  @param[in,out] ybegin       the interator to the upper y value of the current interval
   *  @param[in]     integrator   the integrator to be applied
   */
  template< typename I, typename XIterator, typename YIterator, typename Integrator >
  std::vector< I > cumulativeIntegral( const I& initial,
                                       XIterator& xbegin, const XIterator& xend,
                                       YIterator& ybegin, const Integrator& integrator ) {

    std::vector< I > result( std::distance( xbegin, xend ) + 1 );
    auto previous = result.begin();
    auto current = std::next( previous );
    *previous = initial;

    while ( xbegin != xend ) {

      *current = *previous + integrator( *std::prev( xbegin ), *xbegin, *std::prev( ybegin ), *ybegin );
      previous = current;
      ++current;
      ++xbegin;
      ++ybegin;
    }

    return result;
  }

  /**
   *  @brief Calculate the cumulative integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  @param[in]     initial      the initial value of the cumulative integral to be used
   *                              (i.e. the value of the integral at the end of the previous
   *                              interpolation zone or zero if this is the first region)
   *  @param[in,out] x            the range of x values
   *  @param[in,out] y            the range of y values
   *  @param[in]     integrator   the integrator to be applied
   */
  template< typename I, typename XRange, typename YRange, typename Integrator >
  std::vector< I > cumulativeIntegral( const I& initial,
                                       const XRange& x, const YRange& y,
                                       const Integrator& integrator ) {

    // the iterators point to the end of the first interval
    auto xbegin = std::begin( x ) + 1;
    auto ybegin = std::begin( y ) + 1;
    return cumulativeIntegral( initial, xbegin, x.end(), ybegin, integrator );
  }

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

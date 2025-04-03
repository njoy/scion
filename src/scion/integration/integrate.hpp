#ifndef NJOY_SCION_INTEGRATION_INTEGRATE
#define NJOY_SCION_INTEGRATION_INTEGRATE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @brief Calculate the result of applying an analytical integrator
   *         on tabulated x and y values
   *
   *  @param[in,out] xbegin       the interator to the upper x value of the current interval
   *  @param[in]     xend         the interator to the end of the x values
   *  @param[in,out] ybegin       the interator to the upper y value of the current interval
   *  @param[in]     integrator   the integrator to be applied
   */
  template< typename XIterator, typename YIterator, typename Integrator >
  auto integrate( XIterator& xbegin, const XIterator& xend,
                  YIterator& ybegin, const Integrator& integrator ) {

    auto result = integrator( *xbegin, *xbegin, *ybegin, *ybegin );
    while ( xbegin != xend ) {

      result += integrator( *std::prev( xbegin ), *xbegin, *std::prev( ybegin ), *ybegin );
      ++xbegin;
      ++ybegin;
    }

    return result;
  }

  /**
   *  @brief Calculate the result of applying an analytical integrator
   *         on tabulated x and y values
   *
   *  @param[in,out] x            the range of x values
   *  @param[in,out] y            the range of y values
   *  @param[in]     integrator   the integrator to be applied
   */
  template< typename XRange, typename YRange, typename Integrator >
  auto integrate( const XRange& x, const YRange& y,
                  const Integrator& integrator ) {

    // the iterators point to the end of the first interval
    auto xbegin = std::begin( x ) + 1;
    auto ybegin = std::begin( y ) + 1;
    return integrate( xbegin, x.end(), ybegin, integrator );
  }

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

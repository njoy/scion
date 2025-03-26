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

   */
  template< typename XIterator, typename YIterator, typename Integrator >
  auto integrate( XIterator& xbegin, const XIterator& xend,
                  YIterator& ybegin, const XIterator&,
                  const Integrator& integrator ) {

    auto result = integrator( *xbegin, *xbegin, *ybegin, *ybegin );

    while ( xbegin != xend - 1 ) {

      result += integrator( *xbegin, *std::next( xbegin ), *ybegin, *std::next( ybegin ) );
      ++xbegin;
      ++ybegin;
    }

    return result;
  }

  /**
   *  @brief Calculate the result of applying an analytical integrator
   *         on tabulated x and y values
   */
  template< typename XRange, typename YRange, typename Integrator >
  auto integrate( const XRange& x, const YRange& y,
                  const Integrator& integrator ) {

    auto xbegin = x.begin();
    auto ybegin = y.begin();
    return integrate( xbegin, x.end(), ybegin, y.end(), integrator );
  }

} // integration namespace
} // scion namespace
} // njoy namespace

#endif

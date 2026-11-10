#ifndef NJOY_SCION_INTEGRATION_INTEGRAL
#define NJOY_SCION_INTEGRATION_INTEGRAL

// system includes
#include <algorithm>
#include <iterator>

// other includes

namespace njoy {
namespace scion {
namespace integration {

  /**
   *  @brief Calculate the integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  This calculates the integral over the entire x range.
   *
   *  @param[in,out] xbegin       the interator to the upper x value of the current interval
   *  @param[in]     xend         the interator to the end of the x values
   *  @param[in,out] ybegin       the interator to the upper y value of the current interval
   *  @param[in]     integrator   the integrator to be applied
   */
  template< typename XIterator, typename YIterator, typename Integrator >
  auto integral( XIterator& xbegin, const XIterator& xend,
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
   *  @brief Calculate the integral by applying an analytical integrator
   *         on tabulated x and y values
   *
   *  This calculates the integral over the entire x range.
   *
   *  @param[in] x            the range of x values
   *  @param[in] y            the range of y values
   *  @param[in] integrator   the integrator to be applied
   */
  template< typename XRange, typename YRange, typename Integrator >
  auto integral( const XRange& x, const YRange& y,
                 const Integrator& integrator ) {

    // the iterators point to the end of the first interval
    auto xbegin = std::begin( x ) + 1;
    auto ybegin = std::begin( y ) + 1;
    return integral( xbegin, x.end(), ybegin, integrator );
  }

  /**
   *  @brief Accumulate the integral of tabulated x and y values over a set of groups
   *
   *  This calculates the integral over a user provided set of boundaries.
   *
   *  @param[in]     xbegin         the iterator to the first x value
   *  @param[in]     xend           the iterator to the end of the x values
   *  @param[in]     ybegin         the iterator to the first y value
   *  @param[in]     gbegin         the iterator to the first group boundary
   *  @param[in]     gend           the iterator to the end of the group boundaries
   *  @param[in,out] rbegin         the iterator to the integral for the first group
   *  @param[in]     interpolator   the interpolation function for a panel
   *  @param[in]     integrator     the integration function for a panel
   */
  template < typename XIterator, typename YIterator,
             typename BIterator, typename RIterator,
             typename Interpolator, typename Integrator >
  void integral( XIterator xbegin, XIterator xend, YIterator ybegin,
                 BIterator gbegin, BIterator gend, RIterator rbegin,
                 const Interpolator& interpolator, const Integrator& integrator ) {

    // get the boundaries of the group that contains the first x value
    auto bRight = std::upper_bound( std::next( gbegin ), gend, *xbegin );
    if ( bRight == gend ) {

      // all groups are below the tabulated data
      return;
    }
    auto bLeft = std::prev( bRight );
    if ( ! ( *bLeft < *std::prev( xend ) ) ) {

      // all groups are above the tabulated data
      return;
    }

    // get the corresponding bin to accumulate into
    auto result = std::next( rbegin, std::distance( gbegin, bLeft ) );

    // the x,y values and iterators on the left side of the panel
    auto xLeft = std::max( *bLeft, *xbegin );
    auto xIter = std::upper_bound( std::next( xbegin ), xend, xLeft );
    auto yIter = std::next( ybegin, std::distance( xbegin, xIter ) );
    auto yLeft = xLeft == *std::prev( xIter )
                 ? *std::prev( yIter )
                 : interpolator( xLeft, *std::prev( xIter ), *xIter, *std::prev( yIter ), *yIter );

    const auto& xLast = *std::prev( xend );
    while ( ( bRight != gend ) && ( *bLeft < xLast ) ) {

      const auto xRight = std::min( *bRight, xLast );

      // accumulate panels that end in the current group
      while ( ( xIter != xend ) && ( *xIter <= xRight ) ) {

        *result += integrator( xLeft, *xIter, yLeft, *yIter );
        xLeft = *xIter;
        yLeft = *yIter;
        ++xIter;
        ++yIter;
      }

      // if the group extends past the upper boundary of the panel
      if ( xLeft < xRight ) {

        const auto yRight = interpolator( xRight, *std::prev( xIter ), *xIter,
                                          *std::prev( yIter ), *yIter );
        *result += integrator( xLeft, xRight, yLeft, yRight );
        xLeft = xRight;
        yLeft = yRight;
      }

      // go to the next group
      ++result;
      ++bLeft;
      ++bRight;
    }
  }

  /**
   *  @brief Accumulate the integral of tabulated x and y values over a set of groups
   *
   *  This calculates the integral over a user provided set of boundaries.
   *
   *  @param[in]     x              the range of x values
   *  @param[in]     y              the range of y values
   *  @param[in]     boundaries     the range of boundary values
   *  @param[in,out] integrals      the range of integral values
   *  @param[in]     interpolator   the interpolation function for a panel
   *  @param[in]     integrator     the integration function for a panel
   */
  template < typename XRange, typename YRange,
             typename BRange, typename RRange,
             typename Interpolator, typename Integrator >
  void integral( const XRange& x, const YRange& y,
                 const BRange& boundaries, RRange& integrals,
                 const Interpolator& interpolator, const Integrator& integrator ) {

    integral( x.begin(), x.end(), y.begin(),
              boundaries.begin(), boundaries.end(), integrals.begin(),
              interpolator, integrator );
  }
} // integration namespace
} // scion namespace
} // njoy namespace

#endif

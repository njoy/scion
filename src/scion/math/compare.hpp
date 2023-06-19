#ifndef NJOY_SCION_MATH_COMPARE
#define NJOY_SCION_MATH_COMPARE

// system includes

// other includes

namespace njoy {
namespace scion {
namespace math {

/** @brief Compare two floating point numbers
 *
 *  @param[in] a           the first floating point number to compare
 *  @param[in] b           the second floating point number to compare
 *  @param[in] epsilon     the relative comparison tolerance
 *  @param[in] threshold   the absolute comparison tolerance
 */
template < typename X >
bool isClose( const X& a, const X& b,
              const X& epsilon = X( 100. * std::numeric_limits< double >::epsilon() ),
              const X& threshold = X( 100. * std::numeric_limits< double >::epsilon() ) ) noexcept {

  if ( a == b ) {

    return true;
  }

  const auto diff = std::abs( a - b );
  const auto norm = std::abs( a ) + std::abs( b );
  return diff < std::max( epsilon * norm, threshold );
}

/** @brief Compare a floating point number to zero
 *
 *  @param[in] a           the floating point number to compare to zero
 *  @param[in] threshold   the absolute comparison tolerance
 */
template < typename X >
bool isCloseToZero( const X& a,
                    const X& threshold = X( 100. * std::numeric_limits< double >::epsilon() ) ) noexcept {

  if ( X( 0. ) == a ) {

    return true;
  }

  return std::abs( a ) < threshold;
}

} // math namespace
} // scion namespace
} // njoy namespace

#endif

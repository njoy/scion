#ifndef NJOY_SCION_LINEARISATION_LINEARLINEAR
#define NJOY_SCION_LINEARISATION_LINEARLINEAR

// system includes

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief Linear-linear interpolation
   */
  class LinearLinear {

  public:

    /**
     *  @brief Perform linear-linear interpolation
     */
    template < typename X, typename Y >
    Y interpolate( const X& x, const X& xLeft, const X& xRight,
                   const Y& yRight, const Y& yLeft ) const noexcept {

      return yRight + ( yLeft - yRight ) / ( xLeft - xRight ) * ( x - xRight );
    }

    /**
     *  @brief Perform linear-linear interpolation
     */
    template < typename X, typename Y >
    Y operator()( const X& x, const X& xLeft, const X& xRight,
                  const Y& yRight, const Y& yLeft ) const noexcept {

      return this->interpolate( x, xLeft, xRight, yLeft, yRight );
    }
  };

  // interpolation function
  static constexpr LinearLinear linlin;

} // math namespace
} // scion namespace
} // njoy namespace

#endif

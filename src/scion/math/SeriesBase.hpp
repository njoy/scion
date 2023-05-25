#ifndef NJOY_SCION_MATH_SERIESBASE
#define NJOY_SCION_MATH_SERIESBASE

// system includes

// other includes
#include "scion/math/FunctionBase.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for series expansion objects
   *
   *  This base class provides the common interface for series expansions such
   *  as the polynomial series, Legendre series and Chebyshev series.
   */
  template < typename Derived, typename X, typename Y = X >
  class SeriesBase : public FunctionBase< Derived, X, Y > {

    /* type aliases */
    using Parent = FunctionBase< Derived, X, Y >;

  public:

    /* type aliases */
    using DomainVariant = typename Parent::DomainVariant;

  private:

    /* fields */
    std::vector< Y > coefficients_;

    /* auxiliary function */
    #include "scion/math/SeriesBase/src/verifyCoefficients.hpp"

  protected:

    /* constructor */
    #include "scion/math/SeriesBase/src/ctor.hpp"

  public:

    /* methods */

    /**
     *  @brief Return the Legendre coefficients
     */
    const std::vector< Y >& coefficients() const noexcept {

      return this->coefficients_;
    }

    /**
     *  @brief Return the Legendre order
     */
    unsigned int order() const noexcept {

      return this->coefficients().size() - 1;
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

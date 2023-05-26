#ifndef NJOY_SCION_MATH_SERIESBASE
#define NJOY_SCION_MATH_SERIESBASE

// system includes

// other includes
#include "scion/linearisation/grid.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/linearisation/MidpointSplit.hpp"
#include "scion/linearisation/Lineariser.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "scion/math/FunctionBase.hpp"
#include "scion/math/compare.hpp"
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

    #include "scion/math/SeriesBase/src/roots.hpp"
    #include "scion/math/SeriesBase/src/derivative.hpp"
    #include "scion/math/SeriesBase/src/primitive.hpp"
    #include "scion/math/SeriesBase/src/linearise.hpp"

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    Derived& operator+=( const Y& right ) {

      this->coefficients_[0] += right;
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    Derived& operator-=( const Y& right ) {

      return this->operator+=( -right );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    Derived& operator*=( const Y& right ) {

      for ( auto& value : this->coefficients_ ) {

        value *= right;
      }
      return *static_cast< Derived* >( this );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    Derived& operator/=( const Y& right ) {

      return this->operator*=( Y( 1. ) / right );
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

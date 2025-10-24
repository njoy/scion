#ifndef NJOY_SCION_MATH_POLYNOMIALSERIESRATIO
#define NJOY_SCION_MATH_POLYNOMIALSERIESRATIO

// system includes
#include <vector>

// other includes
#include "scion/math/PolynomialSeries.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/SeriesRatioBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief
   */
  template < typename X, typename Y >
  class PolynomialSeriesRatio :
      public SeriesRatioBase< PolynomialSeriesRatio< X, Y >, PolynomialSeries< X, Y >, X, Y > {

    /* friend declarations */
    friend class SeriesRatioBase< PolynomialSeriesRatio< X, Y >, PolynomialSeries< X, Y >, X, Y >;
    friend class OneDimensionalFunctionBase< PolynomialSeriesRatio< X, Y >, X, Y >;

    /* type aliases */
    using Parent = SeriesRatioBase< PolynomialSeriesRatio< X, Y >, PolynomialSeries< X, Y >, X, Y >;

    /* fields */

    /* auxiliary functions */

    /* interface implementation functions */

  public:

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

    /* constructor */

    #include "scion/math/PolynomialSeriesRatio/src/ctor.hpp"

    /* methods */

    using Parent::numerator;
    using Parent::denominator;
    using Parent::derivative;
    using Parent::operator+;
    using Parent::operator-;
    using Parent::operator*;
    using Parent::operator/;
    using Parent::operator+=;
    using Parent::operator-=;
    using Parent::operator*=;
    using Parent::operator/=;
    using Parent::operator==;
    using Parent::operator!=;
    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

  /**
   *  @brief Scalar and series addition
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeriesRatio< X, Y >
  operator+( const S& left, const PolynomialSeriesRatio< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Series and series addition
   *
   *  @param[in] left     the series
   *  @param[in] right    the series
   */
  template < typename X, typename Y = X >
  PolynomialSeriesRatio< X, Y >
  operator+( const PolynomialSeries< X, Y >& left, const PolynomialSeriesRatio< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and series subtraction
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeriesRatio< X, Y >
  operator-( const S& left, const PolynomialSeriesRatio< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Series and series subtraction
   *
   *  @param[in] left     the series
   *  @param[in] right    the series
   */
  template < typename X, typename Y = X >
  PolynomialSeriesRatio< X, Y >
  operator-( const PolynomialSeries< X, Y >& left, const PolynomialSeriesRatio< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and series multiplication
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeriesRatio< X, Y >
  operator*( const S& left, const PolynomialSeriesRatio< X, Y >& right ) {

    return right * left;
  }

  /**
   *  @brief Series and series multiplication
   *
   *  @param[in] left     the series
   *  @param[in] right    the series
   */
  template < typename X, typename Y = X >
  PolynomialSeriesRatio< X, Y >
  operator*( const PolynomialSeries< X, Y >& left, const PolynomialSeriesRatio< X, Y >& right ) {

    return right * left;
  }

  /**
   *  @brief Scalar and series division
   *
   *  @param[in] left     the scalar
   *  @param[in] right    the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  PolynomialSeriesRatio< X, Y >
  operator/( const S& left, const PolynomialSeriesRatio< X, Y >& right ) {

    PolynomialSeriesRatio< X, Y > result( left * right.denominator(), right.numerator() );
    return result;
  }

  /**
   *  @brief Series and series multiplication
   *
   *  @param[in] left     the series
   *  @param[in] right    the series
   */
  template < typename X, typename Y = X >
  PolynomialSeriesRatio< X, Y >
  operator/( const PolynomialSeries< X, Y >& left, const PolynomialSeriesRatio< X, Y >& right ) {

    PolynomialSeriesRatio< X, Y > result( left * right.denominator(), right.numerator() );
    return result;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

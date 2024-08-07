#ifndef NJOY_SCION_MATH_INTERPOLATIONTABLE
#define NJOY_SCION_MATH_INTERPOLATIONTABLE

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "utility/IteratorView.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/unionisation/unionise.hpp"
#include "scion/math/newton.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/HistogramTable.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "scion/math/LinearLogTable.hpp"
#include "scion/math/LogLinearTable.hpp"
#include "scion/math/LogLogTable.hpp"
#include "scion/math/IntervalDomain.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with one or more interpolation types
   */
  template < typename X, typename Y = X >
  class InterpolationTable :
      public OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y > {

    /* friend declarations */
    friend class OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y >;

    /* type aliases */
    using Parent = OneDimensionalFunctionBase< InterpolationTable< X, Y >, X, Y >;
    using XIterator = typename std::vector< X >::const_iterator;
    using YIterator = typename std::vector< Y >::const_iterator;
    using XContainer = njoy::utility::IteratorView< XIterator >;
    using YContainer = njoy::utility::IteratorView< YIterator >;
    using TableVariant = std::variant<
                             LinearLinearTable< X, Y, XContainer, YContainer >,
                             HistogramTable< X, Y, XContainer, YContainer >,
                             LinearLogTable< X, Y, XContainer, YContainer >,
                             LogLinearTable< X, Y, XContainer, YContainer >,
                             LogLogTable< X, Y, XContainer, YContainer > >;

    /* fields */
    std::vector< X > x_;
    std::vector< Y > y_;
    std::vector< std::size_t > boundaries_;
    std::vector< interpolation::InterpolationType > interpolants_;
    std::vector< TableVariant > tables_;
    bool linearised_;

    /* auxiliary function */
    #include "scion/math/InterpolationTable/src/evaluateOnGrid.hpp"
    #include "scion/math/InterpolationTable/src/operation.hpp"
    #include "scion/math/InterpolationTable/src/generateTables.hpp"
    #include "scion/math/InterpolationTable/src/processBoundaries.hpp"

    /**
     *  @brief Return the interpolation tables
     */
    const std::vector< TableVariant >& tables() const noexcept {

      return this->tables_;
    }

    /* interface implementation functions */
    #include "scion/math/InterpolationTable/src/evaluate.hpp"

  public:

    /* constructor */
    #include "scion/math/InterpolationTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the x values of the table
     */
    const std::vector< X >& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the y values of the table
     */
    const std::vector< Y >& y() const noexcept {

      return this->y_;
    }

    /**
     *  @brief Return the boundaries of the interpolation regions
     */
    const std::vector< std::size_t >& boundaries() const noexcept {

      return this->boundaries_;
    }

    /**
     *  @brief Return the interpolation types of the interpolation regions
     */
    const std::vector< interpolation::InterpolationType >& interpolants() const noexcept {

      return this->interpolants_;
    }

    /**
     *  @brief Return the number of points in the table
     */
    std::size_t numberPoints() const noexcept {

      return this->x().size();
    }

    /**
     *  @brief Return the number of interpolation regions in the table
     */
    std::size_t numberRegions() const noexcept {

      return this->boundaries().size();
    }

    /**
     *  @brief Return whether or not the data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    #include "scion/math/InterpolationTable/src/linearise.hpp"

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator+=( const Y& right ) {

      return this->operation( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator-=( const Y& right ) {

      return this->operation( right, std::minus< Y >() );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator*=( const Y& right ) {

      return this->operation( right, std::multiplies< Y >() );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator/=( const Y& right ) {

      return this->operation( Y( 1. ) / right, std::multiplies< Y >() );
    }

    /**
     *  @brief InterpolationTable and scalar addition
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator+( const Y& right ) const {

      InterpolationTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator-( const Y& right ) const {

      InterpolationTable result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator*( const Y& right ) const {

      InterpolationTable result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar division
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable operator/( const Y& right ) const {

      InterpolationTable result = *this;
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    InterpolationTable operator-() const {

      InterpolationTable result = *this;
      result *= Y( -1. );
      return result;
    }

    /**
     *  @brief Inplace InterpolationTable addition
     *
     *  @param[in] right    the table
     */
    InterpolationTable& operator+=( const InterpolationTable& right ) {

      return this->operation( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace InterpolationTable subtraction
     *
     *  @param[in] right    the table
     */
    InterpolationTable& operator-=( const InterpolationTable& right ) {

      return this->operation( right, std::minus< Y >() );
    }

    /**
     *  @brief InterpolationTable and InterpolationTable addition
     *
     *  @param[in] right    the table
     */
    InterpolationTable operator+( const InterpolationTable& right ) const {

      InterpolationTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief InterpolationTable and InterpolationTable subtraction
     *
     *  @param[in] right    the table
     */
    InterpolationTable operator-( const InterpolationTable& right ) const {

      InterpolationTable result = *this;
      result -= right;
      return result;
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
  };

  /**
   *  @brief Scalar and InterpolationTable addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  InterpolationTable< X, Y >
  operator+( const Y& left, const InterpolationTable< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and InterpolationTable subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  InterpolationTable< X, Y >
  operator-( const Y& left, const InterpolationTable< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and InterpolationTable multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  InterpolationTable< X, Y >
  operator*( const Y& left, const InterpolationTable< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

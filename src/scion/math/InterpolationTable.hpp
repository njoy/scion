#ifndef NJOY_SCION_MATH_INTERPOLATIONTABLE
#define NJOY_SCION_MATH_INTERPOLATIONTABLE

// system includes
#include <algorithm>
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "utility/IteratorView.hpp"
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/unionisation/Unioniser.hpp"
#include "scion/math/newton.hpp"
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "scion/math/HistogramTable.hpp"
#include "scion/math/LinearLinearTable.hpp"
#include "scion/math/LinearLogTable.hpp"
#include "scion/math/LogLinearTable.hpp"
#include "scion/math/LogLogTable.hpp"
#include "scion/math/IntervalDomain.hpp"
#include "scion/verification/ranges.hpp"

#include "scion/math/ConstantWeightFunction.hpp"
#include "scion/math/MeanWeightFunction.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated data with one or more interpolation types
   */
  template < typename X, typename Y >
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

    /* type aliases */

    using typename Parent::XType;
    using typename Parent::YType;
    using typename Parent::DomainVariant;

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

      return this->operationForLinearisedOnly( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    InterpolationTable& operator-=( const Y& right ) {

      return this->operationForLinearisedOnly( right, std::minus< Y >() );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable& operator*=( const S& right ) {

      return this->operation( right, std::multiplies< Y >() );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable& operator/=( const S& right ) {

      return this->operation( right, std::divides< Y >() );
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
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable operator*( const S& right ) const {

      InterpolationTable result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief InterpolationTable and scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    InterpolationTable operator/( const S& right ) const {

      InterpolationTable result = *this;
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    InterpolationTable operator-() const {

      InterpolationTable result = *this;
      result *= -1;
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

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator==( const InterpolationTable& right ) const noexcept {

      return this->domain() == right.domain() &&
             this->interpolants() == right.interpolants() &&
             this->boundaries() == right.boundaries() &&
             this->x() == right.x() &&
             this->y() == right.y();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator!=( const InterpolationTable& right ) const noexcept {

      return ! this->operator==( right );
    }

    using Parent::domain;
    using Parent::operator();

    /**
     *  @brief Calculate the integral of w(x) * f(x) dx over the table domain
     *
     *  The weight function must implement the math::WeightFunctionBase interface.
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) integrate( const WeightFunction& weight ) const {

      auto integrate = [&] ( auto&& region ) -> decltype(auto) {

        return region.integrate( weight );
      };

      auto compute = [&] ( auto&& result, auto&& variant ) -> decltype(auto) {

        return result + std::visit( integrate, variant );
      };

      auto iter = this->tables().begin();
      auto result = std::visit( integrate, *iter );
      ++iter;

      return std::accumulate( iter, this->tables().end(), result, compute );
    }

    /**
     *  @brief Calculate the integral over the table domain
     */
    decltype(auto) integral() const {

      return this->integrate( ConstantWeightFunction< X, double >{ 1. } );
    }

    /**
     *  @brief Calculate the cumulative integral of w(x) * f(x) dx over the table domain
     *
     *  The weight function must implement the math::WeightFunctionBase interface.
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) cumulativeIntegrate( const WeightFunction& weight ) const {

      using I = decltype( weight.integrateHistogram( this->x()[0], this->x()[1], this->y()[0], this->y()[1] ) );

      I first{ 0. };
      auto cumulative = [&] ( auto&& table ) {

        return table.cumulativeIntegrate( first, weight );
      };

      auto check = [this] ( const auto& table ) {

        return table.x().end() != this->x().end()
               ? ( *( table.x().end() ) == table.x().back() )
                 ? ( *( table.y().end() ) != table.y().back() ? true : false )
                 : false
               : true;
      };

      auto iter = this->tables().begin();
      auto result = std::visit( cumulative, *iter );
      ++iter;

      while ( iter != this->tables().end() ) {

        first = result.back();
        auto integrals = std::visit( cumulative, *iter );

        if ( std::visit( check, *std::prev( iter ) ) ) {

          result.insert( result.end(), integrals.begin(), integrals.end() );
        }
        else {

          result.insert( result.end(), std::next( integrals.begin() ), integrals.end() );
        }

        ++iter;
      }

      return result;
    }

    /**
     *  @brief Calculate the cumulative integral over the table domain
     */
    template < typename I = decltype( std::declval< X >() * std::declval< Y >() ) >
    std::vector< I > cumulativeIntegral() const {

      return this->cumulativeIntegrate( ConstantWeightFunction< X, double >{ 1. } );
    }

    /**
     *  @brief Calculate the mean over the table domain
     *
     *  Note: unnormalised and normalised tables return the same mean value.
     */
    X mean() const {

      return this->integrate( MeanWeightFunction< X >{} ) / this->integral();
    }

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
   *  @param[in] right   the series
   */
  template < typename S, typename X, typename Y = X,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  InterpolationTable< X, Y >
  operator*( const S& left, const InterpolationTable< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

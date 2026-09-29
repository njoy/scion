#ifndef NJOY_SCION_MATH_GROUPEDTABLE
#define NJOY_SCION_MATH_GROUPEDTABLE

// system includes
#include <vector>
#include <tuple>
#include <numeric>
#include <functional>

// other includes
#include "tools/Log.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Table to hold grouped y values and the group boundaries.
   *         The size of the y values vector should be one less
   *         than the size of the group boundary values. The
   *         groups are assumed to be contiguous and ascending.
   *
   *  The GroupedTable is templated on the types of the x and y values,
   *  but does require that they are both in vectors.
   */
 template < typename X, typename Y >
 class GroupedTable {

    /* fields */

    std::vector< X > x_;
    std::vector< Y > y_;

    /* auxiliary functions */

    /**
     *  @brief Apply a binary operation involving a scalar of type Y
     *
     *  This function is applied to addition and subtraction
     */
    template < typename BinaryOperation >
    GroupedTable&
    operationForAdditionAndSubtraction( const Y& right, BinaryOperation operation ) {

      std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                      [&right, &operation] ( auto&& y )
                                           { return operation( y, right ); } );

      return *this;
    }

    /**
     *  @brief Apply a binary operation involving a scalar
     *
     *  This function is applied to division and multiplication
     */
    template < typename S, typename BinaryOperation >
    GroupedTable&
    operation( const S& right, BinaryOperation operation ) {

      std::transform( this->y_.cbegin(), this->y_.cend(), this->y_.begin(),
                      [&right, &operation] ( auto&& y )
                                           { return operation( y, right ); } );

      return *this;
    }

    /**
     *  @brief Apply a binary operation involving another GroupedTable
     *
     *  This function is applied to addition and subtraction
     */
    template < typename BinaryOperation >
    GroupedTable&
    operation( const GroupedTable& right, BinaryOperation operation ) {

      // we can only perform the operation if they have the same boundaries
      if ( this->boundaries() == right.boundaries() ) {

        std::transform( this->y_.cbegin(), this->y_.cend(), right.y_.begin(),
                        this->y_.begin(), operation );

        return *this;
      }
      else {

        Log::error( "The operation cannot be performed because both tables do not have the "
                    "same boundaries" );
        Log::info( "left number of groups: {}", this->numberGroups() );
        Log::info( "right number of groups: {}", right.numberGroups() );
        throw std::exception();
      }
    }

    void verifyTable( ) {

      // check sizes - there must be at least two boundaries
      if ( ! verification::isAtLeastOfSize( this->boundaries(), 2 )  ) {

        Log::error( "Insufficient boundary values defined for grouped data "
                "(at least 2 values are required)" );
        Log::info( "Boundary size: {}", this->boundaries().size() );
        throw std::exception();
      }

      // check sizes - bounds must be one longer than values
      if ( this->boundaries().size() != this->values().size() + 1 ) {

        Log::error( "Inconsistent boundaries and values defined for grouped data "
                "(number of boundaries must be one greater than number of values)" );
        Log::info( "Boundaries: {}", this->boundaries().size() );
        Log::info( "Values: {}", this->values().size() );
        throw std::exception();
      }

      // check that the energy values are all increasing, with
      // no repeated values
      if ( ! verification::isSorted( this->boundaries() ) ) {

        Log::error( "The boundary values do not appear to be in ascending order." );
        throw std::exception();
      }

      if ( ! verification::isUnique( this->boundaries() ) ) {

        Log::error( "The boundary values do not appear to be in unique." );
        throw std::exception();
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    GroupedTable() = default;

    /**
     *  @brief Constructor
     *
     *  @param boundaries   the group boundaries (size n)
     *  @param values       the grouped values (size n-1)
     *
     */
    GroupedTable( std::vector< X > boundaries,
                  std::vector< Y > values ) :
        x_( std::move( boundaries ) ), y_( std::move( values ) ) {

      this->verifyTable();
    }

    /* methods */

    /**
     *  @brief Return the group boundaries
     */
    const std::vector< X >& boundaries() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the grouped values
     */
    const std::vector< Y >& values() const noexcept {

      return this->y_;
    }

    /**
     *  @brief Return the number of groups
     */
    std::size_t numberGroups() const noexcept {

      return this->values().size();
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    GroupedTable& operator+=( const Y& right ) {

      return this->operationForAdditionAndSubtraction( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    GroupedTable& operator-=( const Y& right ) {

      return this->operationForAdditionAndSubtraction( right, std::minus< Y >() );
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    GroupedTable& operator*=( const S& right ) {

      return this->operation( right, std::multiplies< Y >() );
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    GroupedTable& operator/=( const S& right ) {

      return this->operation( right, std::divides< Y >() );
    }

    /**
     *  @brief GroupedTable and scalar addition
     *
     *  @param[in] right    the scalar
     */
    GroupedTable operator+( const Y& right ) const {

      GroupedTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief GroupedTable and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    GroupedTable operator-( const Y& right ) const {

      GroupedTable result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief GroupedTable and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    GroupedTable operator*( const S& right ) const {

      GroupedTable result = *this;
      result *= right;
      return result;
    }

    /**
     *  @brief GroupedTable and scalar division
     *
     *  @param[in] right    the scalar
     */
    template < typename S,
               typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
    GroupedTable operator/( const S& right ) const {

      GroupedTable result = *this;
      result /= right;
      return result;
    }

    /**
     *  @brief Unary minus
     */
    GroupedTable operator-() const {

      GroupedTable result = *this;
      result *= -1;
      return result;
    }

    /**
     *  @brief Inplace GroupedTable addition
     *
     *  @param[in] right    the table
     */
    GroupedTable& operator+=( const GroupedTable& right ) {

      return this->operation( right, std::plus< Y >() );
    }

    /**
     *  @brief Inplace GroupedTable subtraction
     *
     *  @param[in] right    the table
     */
    GroupedTable& operator-=( const GroupedTable& right ) {

      return this->operation( right, std::minus< Y >() );
    }

    /**
     *  @brief GroupedTable and GroupedTable addition
     *
     *  @param[in] right    the table
     */
    GroupedTable operator+( const GroupedTable& right ) const {

      GroupedTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief GroupedTable and GroupedTable subtraction
     *
     *  @param[in] right    the table
     */
    GroupedTable operator-( const GroupedTable& right ) const {

      GroupedTable result = *this;
      result -= right;
      return result;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator==( const GroupedTable& right ) const noexcept {

      return std::tie( this->boundaries(), this->values() ) ==
             std::tie( right.boundaries(), right.values() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator!=( const GroupedTable& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and GroupedTable addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  GroupedTable< X, Y >
  operator+( const Y& left, const GroupedTable< X, Y >& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and GroupedTable subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right     the series
   */
  template < typename X, typename Y = X >
  GroupedTable< X, Y >
  operator-( const Y& left, const GroupedTable< X, Y >& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and GroupedTable multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the GroupedTable
   */
  template < typename S, typename X, typename Y,
             typename std::enable_if_t< std::is_arithmetic_v< S >, bool > = true >
  GroupedTable< X, Y > operator*( const S& left, const GroupedTable< X, Y >& right ) {

    return right * left;
  }

} // math namespace
} // scion namespace
} // njoy namespace

#endif

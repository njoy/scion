#ifndef NJOY_SCION_MATH_GROUPEDTABLE
#define NJOY_SCION_MATH_GROUPEDTABLE

// system includes
#include <vector>
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

    std::vector< X > x_;          // vector of group boundary values
    std::vector< Y > y_;          // vector of grouped values

    /* auxiliary functions */

    #include "scion/math/GroupedTable/src/operation.hpp"
    #include "scion/math/GroupedTable/src/verifyTable.hpp"

  public:

    /* constructor */

    #include "scion/math/GroupedTable/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the group boundaries
     */
    const std::vector< X >& bounds() const noexcept {

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
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the table on the right hand side
     */
    bool operator==( const GroupedTable& right ) const noexcept {

      return this->bounds() == right.bounds() &&
             this->values() == right.values();
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

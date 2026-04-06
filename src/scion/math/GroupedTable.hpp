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
   * The GroupedTable is templated on the types of the x and y values, 
   *  but does require that they are both in vectors.
   */
 template < typename X, typename Y >
 class GroupedTable {

    /* fields */                           
    std::vector< X > x_;          // vector of group boundary values
    std::vector< Y > y_;          // vector of grouped values

    /* auxiliary functions */
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

};

} // math namespace
} // scion namespace
} // njoy namespace

#endif

#ifndef NJOY_SCION_INTERPOLATION_TABLE
#define NJOY_SCION_INTERPOLATION_TABLE

// system includes
#include <algorithm>
#include <iterator>

// other includes
#include "utility/Log.hpp"
#include "scion/verification/ranges.hpp"

namespace njoy {
namespace scion {
namespace interpolation {

  /**
   *  @class
   *  @brief Generic table for tabulated data
   */
  template < typename Interpolator, typename XContainer, typename YContainer >
  class Table {

    /* type aliases */
    using X = std::decay_t< decltype( *( std::declval< XContainer >().begin() ) ) >;
    using Y = std::decay_t< decltype( *( std::declval< YContainer >().begin() ) ) >;

    /* fields */
    Interpolator interpolator_;
    XContainer x_;
    YContainer y_;

    /* auxiliary function */
    #include "scion/interpolation/Table/src/verifyTable.hpp"

  public:

    /* constructor */
    #include "scion/interpolation/Table/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the interpolator
     */
    const Interpolator& interpolator() const noexcept {

      return this->interpolator_;
    }

    /**
     *  @brief Return the x values of the table
     */
    const XContainer& x() const noexcept {

      return this->x_;
    }

    /**
     *  @brief Return the y values of the table
     */
    const YContainer& y() const noexcept {

      return this->y_;
    }

    #include "scion/interpolation/Table/src/evaluate.hpp"
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

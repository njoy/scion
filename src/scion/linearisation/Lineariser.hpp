#ifndef NJOY_SCION_LINEARISATION_LINEARISER
#define NJOY_SCION_LINEARISATION_LINEARISER

// system includes
#include <functional>
#include <utility>
#include <vector>

// other includes

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief A generic linearisation object
   */
  template < typename XContainer, typename YContainer >
  class Lineariser {

    /* type aliases */
    using X = typename XContainer::value_type;
    using Y = typename XContainer::value_type;

    /* fields */
    std::reference_wrapper< XContainer > x_;
    std::reference_wrapper< YContainer > y_;
    std::vector< X > xbuffer_;
    std::vector< Y > ybuffer_;

    /* auxiliary function */
    #include "scion/linearisation/Lineariser/src/panel.hpp"

  public:

    /* constructor */
    #include "scion/linearisation/Lineariser/src/ctor.hpp"

    /* methods */
    #include "scion/linearisation/Lineariser/src/call.hpp"
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

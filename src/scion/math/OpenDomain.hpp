#ifndef NJOY_SCION_MATH_OPENDOMAIN
#define NJOY_SCION_MATH_OPENDOMAIN

// system includes

// other includes

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A domain for a function y -> f(x) including any value of x
   *
   *  This class is defined as a template class for a given type X (e.g. int,
   *  double, etc.). There are no requirements on the interface of X for this
   *  class.
   */
  template < typename X >
  class OpenDomain {

    /* fields */

    /* auxiliary function */

  public:

    /* constructor */
    OpenDomain() = default;

    /* methods */

    /**
     *  @brief Check whether or not a value is inside the domain (including
     *         boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isInside( const X& ) const noexcept {

      return true;
    }

    /**
     *  @brief Check whether or not a value is contained within the domain
     *         (excluding boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isContained( const X& ) const noexcept {

      return true;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the domain on the right hand side
     */
    bool operator==( const OpenDomain& right ) const noexcept {

      return true;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the domain on the right hand side
     */
    bool operator!=( const OpenDomain& right ) const noexcept {

      return false;
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

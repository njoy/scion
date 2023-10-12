#ifndef NJOY_SCION_MATH_INTERVALDOMAIN
#define NJOY_SCION_MATH_INTERVALDOMAIN

// system includes

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief A domain for a function y -> f(x) for x inside [a,b]
   *
   *  This class is defined as a template class for a given type X (e.g. int,
   *  double, etc.). This class requires the following functions to be defined
   *  on the X type: operator<() and operator==()
   */
  template < typename X >
  class IntervalDomain {

    /* fields */
    X lower_;
    X upper_;

    /* auxiliary function */
    #include "scion/math/IntervalDomain/src/verifyDomain.hpp"

  public:

    /* constructor */
    #include "scion/math/IntervalDomain/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the lower limit of the domain
     */
    const X& lowerLimit() const noexcept {

      return lower_;
    }

    /**
     *  @brief Return the upper limit of the domain
     */
    const X& upperLimit() const noexcept {

      return upper_;
    }

    /**
     *  @brief Check whether or not a value is inside the domain (including
     *         boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isInside( const X& x ) const noexcept {

      if ( ( x < this->lowerLimit() ) || ( this->upperLimit() < x ) ) {

        return false;
      }
      return true;
    }

    /**
     *  @brief Check whether or not a value is contained within the domain
     *         (excluding boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isContained( const X& x ) const noexcept {

      if ( ( this->lowerLimit() < x ) && ( x < this->upperLimit() ) ) {

        return true;
      }
      return false;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the domain on the right hand side
     */
    bool operator==( const IntervalDomain& right ) const noexcept {

      return ( ( this->lowerLimit() == right.lowerLimit() ) &&
               ( this->upperLimit() == right.upperLimit() ) );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the domain on the right hand side
     */
    bool operator!=( const IntervalDomain& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

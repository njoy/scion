#ifndef NJOY_SCION_MATH_FUNCTIONBASE
#define NJOY_SCION_MATH_FUNCTIONBASE

// system includes
#include <variant>

// other includes
#include "scion/math/IntervalDomain.hpp"
#include "scion/math/OpenDomain.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Base class for function objects
   *
   *  This base class provides the common interface for all function objects.
   *  This includes domain testing and function evaluation.
   */
  template < typename Derived, typename X, typename Y = X >
  class FunctionBase {

  public:

    /* type aliases */
    using DomainVariant = std::variant< IntervalDomain< X >, OpenDomain< X > >;

  private:

    /* fields */
    DomainVariant domain_;

    /* auxiliary function */

  protected:

    /* constructor */
    #include "scion/math/FunctionBase/src/ctor.hpp"

  public:

    /* methods */

    /**
     *  @brief Check whether or not a value is inside the domain (including
     *         boundaries)
     *
     *  @param x   the value to be tested
     */
    const DomainVariant& domain() const noexcept {

      return this->domain_;
    }

    /**
     *  @brief Evaluate the function for a value of x
     *
     *  @param x   the value to be evaluated
     */
    Y operator()( const X& x ) const {

      return static_cast< const Derived* >( this )->evaluate( x );
    }

    /**
     *  @brief Check whether or not a value is inside the domain (including
     *         boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isInside( const X& x ) const noexcept {

      return std::visit( [&x] ( const auto& domain )
                              { return domain.isInside( x ); },
                         this->domain() );
    }

    /**
     *  @brief Check whether or not a value is contained within the domain
     *         (excluding boundaries)
     *
     *  @param x   the value to be tested
     */
    bool isContained( const X& x ) const noexcept {

      return std::visit( [&x] ( const auto& domain )
                              { return domain.isContained( x ); },
                         this->domain() );
    }

    /**
     *  @brief Check whether or not a domain is equal to the function's domain
     *
     *  @param domain   the domain to be tested
     */
    bool isSameDomain( const DomainVariant& domain ) const noexcept {

      return this->domain() == domain;
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

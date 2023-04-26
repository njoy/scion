#ifndef NJOY_SCION_LINEARISATION_TOLERANCECONVERGENCE
#define NJOY_SCION_LINEARISATION_TOLERANCECONVERGENCE

// system includes

// other includes
#include "scion/linearisation/ConvergenceBase.hpp"

namespace njoy {
namespace scion {
namespace linearisation {

  /**
   *  @class
   *  @brief A convergence functor using a single tolerance
   *
   *  This functor class can be used to ensure convergence of the linearisation
   *  process using a relative tolerance and absolute difference threshold.
   *  With this functor, a trial value and reference value are considered
   *  converged if:
   *    abs( trial - reference ) < ( abs( trial ) + abs( reference ) ) * tolerance
   *
   *  For very small values (when ( abs( trial ) + abs( reference ) ) * tolerance
   *  is smaller than the threshold value), a trial value and reference value
   *  are considered converged if:
   *    abs( trial - reference ) < threshold
   */
  template< typename X, typename Y = X >
  class ToleranceConvergence : public ConvergenceBase< ToleranceConvergence< X, Y >, X, Y > {

    /* type aliases */
    using Parent = ConvergenceBase< ToleranceConvergence< X, Y >, X, Y >;

    /* fields */
    Y tolerance_;
    Y threshold_;

    /* auxiliary function */

  public:

    /* constructor */
    #include "scion/linearisation/ToleranceConvergence/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the linearisation tolerance
     */
    const Y& tolerance() const {

      return this->tolerance_;
    }

    /**
     *  @brief Return the linearisation threshold
     */
    const Y& threshold() const {

      return this->threshold_;
    }

    /**
     *  @brief Verify convergence of the linearisation using a simple tolerance
     *
     *  @param[in] trial        the trial value to be tested
     *  @param[in] reference    the reference value to be tested against
     *
     *  The last 4 arguments imposed by the ConvergenceBase class are not used.
     */
    bool evaluate( const Y& trial, const Y& reference,
                   const X&      , const X&          ,
                   const Y&      , const Y&            ) const {

      if ( trial == reference ) {

        return true;
      }

      const auto diff = std::abs( trial - reference );
      const auto norm = std::abs( reference );
      return diff < std::max( this->tolerance() * norm, this->threshold() );
    }

    using Parent::operator();
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif
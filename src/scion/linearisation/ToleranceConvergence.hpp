#ifndef NJOY_SCION_LINEARISATION_TOLERANCECONVERGENCE
#define NJOY_SCION_LINEARISATION_TOLERANCECONVERGENCE

// system includes
#include <cmath>

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
   *  process using a relative tolerance criterion, normalized by the reference
   *  value, with the threshold acting as an absolute difference floor when the
   *  reference value is close to zero. With this functor, a trial value and
   *  reference value are considered converged if:
   *    abs( trial - reference ) < max( abs( reference ) * tolerance, threshold )
   */
  template< typename X, typename Y = X >
  class ToleranceConvergence : public ConvergenceBase< ToleranceConvergence< X, Y >, X, Y > {

    /* friend declarations */
    friend class ConvergenceBase< ToleranceConvergence< X, Y >, X, Y >;

    /* type aliases */
    using Parent = ConvergenceBase< ToleranceConvergence< X, Y >, X, Y >;

    /* fields */
    Y tolerance_;
    Y threshold_;

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Verify convergence of the linearisation using a simple tolerance
     *
     *  @param[in] trial        the trial value to be tested
     *  @param[in] reference    the reference value to be tested against
     *
     *  The last 4 arguments imposed by the ConvergenceBase class are not used.
     */
    bool hasConverged( const Y& trial, const Y& reference,
                       const X&      , const X&          ,
                       const Y&      , const Y&            ) const {

      if ( trial == reference ) {

        return true;
      }

      const auto diff = std::abs( trial - reference );
      const auto norm = std::abs( reference );
      return diff < std::max( this->tolerance() * norm, this->threshold() );
    }

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

    using Parent::operator();
  };

} // linearisation namespace
} // scion namespace
} // njoy namespace

#endif

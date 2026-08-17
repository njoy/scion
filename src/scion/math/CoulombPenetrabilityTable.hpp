#ifndef NJOY_SCION_MATH_COULOMBPENETRABILITYTABLE
#define NJOY_SCION_MATH_COULOMBPENETRABILITYTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/CoulombPenetrability.hpp"
#include "scion/math/SingleTableBase.hpp"
#include "scion/integration/integral.hpp"
#include "scion/integration/cumulativeIntegral.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,y data with Coulomb Penetrability interpolation (LAW=6)
   *
   *  The CoulombPenetrabilityTable is constructed with the threshold value
   *  and that becomes an attribute of the table object.
   */
  template < typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class CoulombPenetrabilityTable :
    public SingleTableBase< CoulombPenetrabilityTable< X, Y, XContainer, YContainer >,
                            X, Y, XContainer, YContainer > {

    /* friend declarations */
    friend class SingleTableBase< CoulombPenetrabilityTable< X, Y, XContainer, YContainer >,
                                  X, Y, XContainer, YContainer >;

    /* type aliases */
    using Parent = SingleTableBase< CoulombPenetrabilityTable< X, Y, XContainer, YContainer >,
                                    X, Y, XContainer, YContainer >;

    /* fields */
    X threshold_;
    njoy::scion::interpolation::CoulombPenetrability< X, Y > interpolator_;

    /* auxiliary function */
    #include "scion/math/CoulombPenetrabilityTable/src/verifyTable.hpp"

    /* interface implementation functions */


  public:

    #include "scion/math/CoulombPenetrabilityTable/src/evaluate.hpp"


    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param x           the x values of the tabulated data
     *  @param y           the y values of the tabulated data
     *  @param threshold   the threshold value
     */
    CoulombPenetrabilityTable( XContainer x, YContainer y, X threshold ) :
      Parent( std::move( x ), std::move( y ) ),
      threshold_( threshold ),
      interpolator_( threshold ) {

        verifyTable( this->x(), this->threshold() );
      }


    CoulombPenetrabilityTable( const CoulombPenetrabilityTable& ) = default;
    CoulombPenetrabilityTable( CoulombPenetrabilityTable&& ) = default;

    CoulombPenetrabilityTable& operator=( const CoulombPenetrabilityTable& ) = default;
    CoulombPenetrabilityTable& operator=( CoulombPenetrabilityTable&& ) = default;



    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::CoulombPenetrability;
    }

    /**
     *  @brief Return the threshold value
     */
    const X& threshold() const noexcept {

      return this->threshold_;
    }

    /**
     *  @brief Interpolate
     *
     *  @param[in] x        the value of x
     *  @param[in] xLeft    the left value on the x interval
     *  @param[in] xRight   the right value on the x interval
     *  @param[in] yLeft    the left value on the y interval
     *  @param[in] yRight   the right value on the y interval
     */
    Y interpolate( const X& x,
                  const X& xLeft, const X& xRight,
                  const Y& yLeft, const Y& yRight ) noexcept {

      return this->interpolator_( x, xLeft, xRight, yLeft, yRight );
    }

    /**
     *  @brief Calculate the integral of w(x) * f(x) dx over the interpolation region
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) integrate( const WeightFunction& weight ) const {

      auto integrator = [&] ( const X& xLeft, const X& xRight,
                              const Y& yLeft, const Y& yRight ) -> decltype(auto) {

        return weight.integrateCoulombPenetrability( xLeft, xRight, yLeft, yRight, this->threshold_ );
      };
      return integration::integral( this->x(), this->y(), integrator );
    }


    /**
     *  @brief Calculate the cumulative integral of w(x) * f(x) dx over the interpolation region
     *
     *  @param[in] initial   the initial value of the cumulative integral to be used
     *                       (i.e. the value of the integral at the end of the previous
     *                       interpolation zone or zero if this is the first region)
     *  @param[in] weight    the weight function
     */
    template < typename I, typename WeightFunction >
    std::vector< I > cumulativeIntegrate( const I& initial, const WeightFunction& weight ) const {

      auto integrator = [&] ( const X& xLeft, const X& xRight,
                              const Y& yLeft, const Y& yRight ) -> decltype(auto) {

        return weight.integrateCoulombPenetrability( xLeft, xRight, yLeft, yRight, this->threshold_ );
      };
      return integration::cumulativeIntegral( initial, this->x(), this->y(), integrator );
    }

    using Parent::domain;
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;
    using Parent::linearise;

  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

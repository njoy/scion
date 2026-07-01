#ifndef NJOY_SCION_MATH_LINEARLINEARTABLE
#define NJOY_SCION_MATH_LINEARLINEARTABLE

// system includes
#include <vector>

// other includes
#include "scion/interpolation/InterpolationType.hpp"
#include "scion/interpolation/LinearLinear.hpp"
#include "scion/integration/integral.hpp"
#include "scion/integration/cumulativeIntegral.hpp"
#include "scion/linearisation/ToleranceConvergence.hpp"
#include "scion/math/SingleTableBase.hpp"

namespace njoy {
namespace scion {
namespace math {

  /**
   *  @class
   *  @brief Tabulated x,y data with linear-linear interpolation (y is linear in x)
   *
   *  The LinearLinearTable is templatised on the container type used for the
   *  x and y values in addition to the actual x and y types. This allows us to
   *  use something like utility::IteratorView instead of std::vector.
   */
  template < typename X, typename Y,
             typename XContainer = std::vector< X >,
             typename YContainer = std::vector< Y > >
  class LinearLinearTable :
    public SingleTableBase< LinearLinearTable< X, Y, XContainer, YContainer >,
                            X, Y, XContainer, YContainer > {

    /* friend declarations */
    friend class SingleTableBase< LinearLinearTable< X, Y, XContainer, YContainer >,
                                  X, Y, XContainer, YContainer >;

    /* type aliases */
    using Parent = SingleTableBase< LinearLinearTable< X, Y, XContainer, YContainer >,
                                    X, Y, XContainer, YContainer >;

    /* fields */

    /* auxiliary function */

    /* interface implementation functions */

    /**
     *  @brief Return the interpolation type
     */
    static constexpr interpolation::InterpolationType type() noexcept {

      return interpolation::InterpolationType::LinearLinear;
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
    static constexpr Y interpolate( const X& x,
                                    const X& xLeft, const X& xRight,
                                    const Y& yLeft, const Y& yRight ) noexcept {

      return interpolation::linlin( x, xLeft, xRight, yLeft, yRight );
    }

  public:

    /* constructor */
    #include "scion/math/LinearLinearTable/src/ctor.hpp"

    /* methods */

    using Parent::interpolation;
    using Parent::x;
    using Parent::y;
    using Parent::numberPoints;

    /**
     *  @brief Linearise the table and return a LinearLinearTable
     *
     *  Note: this function returns a copy of the original table.
     *
     *  @param[in] convergence    the linearisation convergence criterion (default 0.1 %)
     */
    template < typename Convergence = linearisation::ToleranceConvergence< X, Y > >
    std::pair< std::vector< X >, std::vector< Y > >
    linearise( Convergence&& = Convergence() ) const {

      return { std::vector< X >{ this->x().begin(), this->x().end() },
               std::vector< Y >{ this->y().begin(), this->y().end() } };
    }

    using Parent::domain;
    using Parent::operator();
    using Parent::isInside;
    using Parent::isContained;
    using Parent::isSameDomain;

    /**
     *  @brief Calculate the integral of w(x) * f(x) dx over the interpolation region
     *
     *  @param[in] weight   the weight function
     */
    template < typename WeightFunction >
    decltype(auto) integrate( const WeightFunction& weight ) const {

      auto integrator = [&] ( const X& xLeft, const X& xRight,
                              const Y& yLeft, const Y& yRight ) -> decltype(auto) {

        return weight.integrateLinearLinear( xLeft, xRight, yLeft, yRight );
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

        return weight.integrateLinearLinear( xLeft, xRight, yLeft, yRight );
      };
      return integration::cumulativeIntegral( initial, this->x(), this->y(), integrator );
    }
  };

} // math namespace
} // scion namespace
} // njoy namespace

#endif

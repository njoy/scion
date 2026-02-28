// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/AdaptiveGaussLobatto.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Adaptive Gauss-Lobatto quadrature" ) {

  GIVEN( "an adaptive Gauss-Lobattointegration object" ) {

    integration::AdaptiveGaussLobatto< double > integrator{};

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed exactly for an order 0 polynomial" ) {

        // y = f(x) = 1
        auto functor = [] ( double x ) { return 1.; };

        CHECK_THAT( 2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 1 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x + 1.; };

        CHECK_THAT(  2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 10., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed for cosine on [-1,1] for different tolerances" ) {

        // y = f(x) = cosine( x )
        auto functor = [] ( double x ) { return std::cos( x ); };

        CHECK_THAT( 2. * std::sin( 1. ), WithinRel( integrator( functor, -1.,  1. ), 1e-8 ) );
        CHECK_THAT( 2. * std::sin( 1. ), WithinRel( integrator( functor, -1.,  1., 1e-12 ), 5e-12 ) );
      } // THEN

      THEN( "the integration is performed for sine on [-1,1] for different tolerances" ) {

        // y = f(x) = sine( x )
        auto functor = [] ( double x ) { return std::sin( x ); };

        CHECK_THAT( 0., WithinRel( integrator( functor, -1.,  1. ), 1e-8 ) );
        CHECK_THAT( 0., WithinRel( integrator( functor, -1.,  1., 1e-12 ), 5e-12 ) );
      } // THEN

      THEN( "the integration is performed for 1/(1+x) on [0,1] for different tolerances" ) {

        // y = f(x) = 1 / ( 1 + x )
        auto functor = [] ( double x ) { return 1. / ( 1. + x ); };

        CHECK_THAT( std::log( 2. ), WithinRel( integrator( functor, 0.,  1. ), 1e-8 ) );
        CHECK_THAT( std::log( 2. ), WithinRel( integrator( functor, 0.,  1., 1e-12 ), 5e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

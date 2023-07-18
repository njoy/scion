// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/GaussLobatto/2.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Gauss-Lobatto 2-point quadrature rule" ) {

  GIVEN( "a Gauss-Lobatto 2-point integration object" ) {

    WHEN( "integrating the [-1,1] interval" ) {

      integration::GaussLobatto< 2, double > integrator{};

      THEN( "the integration is performed exactly for an order 0 polynomial" ) {

        // y = f(x) = 1
        auto functor = [] ( double x ) { return 1.; };

        CHECK_THAT( 2., WithinRel( integrator( functor ) ) );
        CHECK_THAT( 2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 1 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x + 1.; };

        CHECK_THAT(  2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(  2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 10., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
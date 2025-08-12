// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/GaussLobatto/32.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Gauss-Lobatto 32-point quadrature rule" ) {

  GIVEN( "a Gauss-Lobatto 32-point integration object" ) {

    WHEN( "integrating the [-1,1] interval" ) {

      integration::GaussLobatto< 32, double > integrator{};

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

      THEN( "the integration is performed exactly for an order 2 polynomial" ) {

        // y = f(x) = x**2 + 1
        auto functor = [] ( double x ) { return x * x + 1.; };

        CHECK_THAT(  2.66666666666666, WithinRel( integrator( functor ) ) );
        CHECK_THAT(  2.66666666666666, WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 34.66666666666666, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 3 polynomial" ) {

        // y = f(x) = x**3 + 1
        auto functor = [] ( double x ) { return x * x * x + 1.; };

        CHECK_THAT(   2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(   2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 138., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 5 polynomial" ) {

        // y = f(x) = x**5 + 1
        auto functor = [] ( double x ) { return std::pow( x, 5 ) + 1.; };

        CHECK_THAT(                    2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(                    2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2.484666666666666e+03, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 9 polynomial" ) {

        // y = f(x) = x**9 + 1
        auto functor = [] ( double x ) { return std::pow( x, 9 ) + 1.; };

        CHECK_THAT(                    2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(                    2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 9.706596000000000e+05, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 13 polynomial" ) {

        // y = f(x) = x**13 + 1
        auto functor = [] ( double x ) { return std::pow( x, 13 ) + 1.; };

        CHECK_THAT(                    2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(                    2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 4.356237631428570e+08, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 17 polynomial" ) {

        // y = f(x) = x**17 + 1
        auto functor = [] ( double x ) { return std::pow( x, 17 ) + 1.; };

        CHECK_THAT(                    2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(                    2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2.119061025095556e+11, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

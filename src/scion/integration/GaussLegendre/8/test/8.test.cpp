// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/GaussLegendre/8.hpp"

// other includes
#include <cmath>

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Gauss-Legendre 8-point quadrature rule" ) {

  GIVEN( "a Gauss-Legendre 8-point integration object" ) {

    WHEN( "integrating the [-1,1] interval" ) {

      integration::GaussLegendre< 8, double > integrator{};

      THEN( "the integration is performed exactly for an order 0 polynomial" ) {

        // y = f(x) = x + 1
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

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x * x + 1.; };

        CHECK_THAT(  2.66666666666666, WithinRel( integrator( functor ) ) );
        CHECK_THAT(  2.66666666666666, WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 34.66666666666666, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 3 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x * x * x + 1.; };

        CHECK_THAT(   2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(   2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 138., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 7 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return std::pow( x, 7 ) + 1.; };

        CHECK_THAT(     2., WithinRel( integrator( functor ) ) );
        CHECK_THAT(     2., WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 48010., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 11 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return std::pow( x, 11 ) + 1.; };

        CHECK_THAT( 2.                  , WithinRel( integrator( functor ) ) );
        CHECK_THAT( 2.                  , WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 2.030076733333333e+7, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 13 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return std::pow( x, 13 ) + 1.; };

        CHECK_THAT( 2.                  , WithinRel( integrator( functor ) ) );
        CHECK_THAT( 2.                  , WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 4.356237631428576e+8, WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN

      THEN( "the integration is performed exactly for an order 15 polynomial" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return std::pow( x, 15 ) + 1.; };

        CHECK_THAT( 2.         , WithinRel( integrator( functor ) ) );
        CHECK_THAT( 2.         , WithinRel( integrator( functor, -1.,  1. ) ) );
        CHECK_THAT( 9534052746., WithinRel( integrator( functor,  3.,  5. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

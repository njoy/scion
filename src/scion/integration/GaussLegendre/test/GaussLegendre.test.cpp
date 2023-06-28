// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/GaussLegendre.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Gauss-Legendre quadrature rules" ) {

  GIVEN( "Gauss-Legendre 2-point integration object" ) {

    WHEN( "integrating the [-1,1] interval" ) {

      integration::GaussLegendre< 2, double > integrator{};

      THEN( "the integration is performed correctly" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x + 1.; };

        CHECK_THAT( 2., WithinRel( integrator( functor ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "Gauss-Legendre 7-point integration object" ) {

    WHEN( "integrating the [-1,1] interval" ) {

      integration::GaussLegendre< 7, double > integrator{};

      THEN( "the integration is performed correctly" ) {

        // y = f(x) = x + 1
        auto functor = [] ( double x ) { return x + 1.; };

        CHECK_THAT( 2., WithinRel( integrator( functor ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/Histogram.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "Histogram" ) {

  GIVEN( "Histogram integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::Histogram integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // different x values
        CHECK_THAT( 1., WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );

        // equal x values
        CHECK_THAT( 0., WithinRel( integrator( xLeft, xLeft, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "histogram integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // different x values
        CHECK_THAT( 1., WithinRel( integration::histogram( xLeft, xRight, yLeft, yRight ) ) );

        // equal x values
        CHECK_THAT( 0., WithinRel( integration::histogram( xLeft, xLeft, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

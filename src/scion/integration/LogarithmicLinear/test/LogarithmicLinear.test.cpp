// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "scion/integration/LogarithmicLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LogarithmicLinear" ) {

  GIVEN( "LogarithmicLinear integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::LogarithmicLinear integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // different x values
        CHECK_THAT( 2.16404256133345, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );

        // equal x values
        CHECK_THAT( 0., WithinAbs( integrator( xLeft, xLeft, yLeft, yRight ), 1e-12 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "loglin integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        CHECK_THAT( 2.16404256133345, WithinRel( integration::loglin( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

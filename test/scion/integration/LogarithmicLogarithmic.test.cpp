// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/LogarithmicLogarithmic.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LogarithmicLogarithmic" ) {

  GIVEN( "LogarithmicLogarithmic integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::LogarithmicLogarithmic integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0., WithinRel( integrator( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042803497366203e-06, WithinRel( integrator( xLeft, xLeft + 1e-6, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042740629471738e-09, WithinRel( integrator( xLeft, xLeft + 1e-9, yLeft, yRight ) ) );

        // both y values are the same or close to one another
        CHECK_THAT( 1., WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );
        CHECK_THAT( 1.000000557304876470e+00, WithinRel( integrator( xLeft, xRight, yLeft, yLeft + 1e-6 ) ) );
        CHECK_THAT( 1.000000000557305091e+00, WithinRel( integrator( xLeft, xRight, yLeft, yLeft + 1e-9 ) ) );

        // the y values are different
        CHECK_THAT( 2.33333333333333, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "loglog integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0., WithinRel( integration::loglog( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042803497366203e-06, WithinRel( integration::loglog( xLeft, xLeft + 1e-6, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042740629471738e-09, WithinRel( integration::loglog( xLeft, xLeft + 1e-9, yLeft, yRight ) ) );

        // both y values are the same or close to one another
        CHECK_THAT( 1., WithinRel( integration::loglog( xLeft, xRight, yLeft, yLeft ) ) );
        CHECK_THAT( 1.000000557304876470e+00, WithinRel( integration::loglog( xLeft, xRight, yLeft, yLeft + 1e-6 ) ) );
        CHECK_THAT( 1.000000000557305091e+00, WithinRel( integration::loglog( xLeft, xRight, yLeft, yLeft + 1e-9 ) ) );

        // the y values are different
        CHECK_THAT( 2.33333333333333, WithinRel( integration::loglog( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

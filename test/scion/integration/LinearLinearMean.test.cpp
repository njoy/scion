// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/LinearLinearMean.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LinearLinearMean" ) {

  GIVEN( "LinearLinearMean integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::LinearLinearMean integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0. , WithinRel( integrator( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.5000015e-06, WithinRel( integrator( xLeft, xLeft + 1e-6, yLeft, yRight ), 1e-10 ) );
        CHECK_THAT( 2.5000000015e-09, WithinRel( integrator( xLeft, xLeft + 1e-9, yLeft, yRight ), 1e-7 ) );

        // both y values are the same
        CHECK_THAT( 1.5, WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 4.0, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlin integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0. , WithinRel( integration::linLinMean( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.5000015e-06, WithinRel( integration::linLinMean( xLeft, xLeft + 1e-6, yLeft, yRight ), 1e-10 ) );
        CHECK_THAT( 2.5000000015e-09, WithinRel( integration::linLinMean( xLeft, xLeft + 1e-9, yLeft, yRight ), 1e-7 ) );

        // both y values are the same
        CHECK_THAT( 1.5, WithinRel( integration::linLinMean( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 4.0, WithinRel( integration::linLinMean( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

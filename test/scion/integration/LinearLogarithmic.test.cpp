// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/LinearLogarithmic.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LinearLogarithmic" ) {

  GIVEN( "LinearLogarithmic integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::LinearLogarithmic integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0. , WithinRel( integrator( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.5000002499998749e-06, WithinRel( integrator( xLeft, xLeft + 1e-6, yLeft, yRight ), 1e-10 ) );
        CHECK_THAT( 2.5000000002500002e-09, WithinRel( integrator( xLeft, xLeft + 1e-9, yLeft, yRight ), 1e-7 ) );

        // both y values are the same
        CHECK_THAT( 1., WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 2.67191487733311, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linlog integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0. , WithinRel( integration::linlog( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.5000002499998749e-06, WithinRel( integration::linlog( xLeft, xLeft + 1e-6, yLeft, yRight ), 1e-10 ) );
        CHECK_THAT( 2.5000000002500002e-09, WithinRel( integration::linlog( xLeft, xLeft + 1e-9, yLeft, yRight ), 1e-7 ) );

        // both y values are the same
        CHECK_THAT( 1., WithinRel( integration::linlog( xLeft, xRight, yLeft, yLeft ) ) );

        // the y values are different
        CHECK_THAT( 2.67191487733311, WithinRel( integration::linlog( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

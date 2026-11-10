// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/LogarithmicLogarithmicMean.hpp"
#include "scion/integration.hpp"

// other includes
#include <iostream>
#include <iomanip>
// convenience typedefs
using namespace njoy::scion;

SCENARIO( "LogarithmicLogarithmicMean" ) {

  GIVEN( "LogarithmicLogarithmicMean integration object" ) {

    WHEN( "integrating an interval" ) {

      integration::LogarithmicLogarithmicMean integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0., WithinRel( integrator( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.164044127860849784e-06, WithinRel( integrator( xLeft, xLeft + 1e-6, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042741953835048e-09, WithinRel( integrator( xLeft, xLeft + 1e-9, yLeft, yRight ) ) );

        // both y values are the same or close to one another
        CHECK_THAT( 1.5, WithinRel( integrator( xLeft, xRight, yLeft, yLeft ) ) );
        CHECK_THAT( 1.500000917978598025e+00, WithinRel( integrator( xLeft, xRight, yLeft, yLeft + 1e-6 ) ) );
        CHECK_THAT( 1.500000000917978804e+00, WithinRel( integrator( xLeft, xRight, yLeft, yLeft + 1e-9 ) ) );

        // the y values are different
        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4)/ln(2) ln(x) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.75, WithinRel( integrator( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "loglog mean integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 1.0;
        double xRight = 2.0;
        double yLeft = 1.0;
        double yRight = 4.0;

        // both x values are the same or close to one another
        CHECK_THAT( 0., WithinRel( integration::logLogMean( xLeft, xLeft, yLeft, yRight ) ) );
        CHECK_THAT( 2.164044127860849784e-06, WithinRel( integration::logLogMean( xLeft, xLeft + 1e-6, yLeft, yRight ) ) );
        CHECK_THAT( 2.164042741953835048e-09, WithinRel( integration::logLogMean( xLeft, xLeft + 1e-9, yLeft, yRight ) ) );

        // both y values are the same or close to one another
        CHECK_THAT( 1.5, WithinRel( integration::logLogMean( xLeft, xRight, yLeft, yLeft ) ) );
        CHECK_THAT( 1.500000917978598025e+00, WithinRel( integration::logLogMean( xLeft, xRight, yLeft, yLeft + 1e-6 ) ) );
        CHECK_THAT( 1.500000000917978804e+00, WithinRel( integration::logLogMean( xLeft, xRight, yLeft, yLeft + 1e-9 ) ) );

        // the y values are different
        // this value was calculated using Wolfram Alpha using this command:
        // "integrate x exp( ln(4)/ln(2) ln(x) ) dx between 1 and 2"
        // it was verified using Gauss-Legendre 64 quadrature as well
        CHECK_THAT( 3.75, WithinRel( integration::logLogMean( xLeft, xRight, yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

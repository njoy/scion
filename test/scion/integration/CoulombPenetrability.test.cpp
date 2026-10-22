// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/CoulombPenetrability.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "CoulombPenetrability" ) {

  GIVEN( "CoulombPenetrability integration object" ) {

    WHEN( "integrating an interval with threshold = 0.3" ) {

      integration::CoulombPenetrability integrator{};

      THEN( "the integration is performed correctly" ) {

        double xLeft = 2.0;
        double xRight = 7.0;
        double yLeft = 10.0;
        double yRight = 30.0;
        double threshold = 0.3;

        // different x values
        CHECK_THAT( 116.47154112769871, WithinRel( integrator( xLeft, xRight, yLeft, yRight, threshold ), 1e-8 ) );
        CHECK_THAT( 41.94080794793308, WithinRel( integrator( 2.4, 4.5, 13.40080679, 24.91047597, threshold ), 1e-8 ) );

        // equal x values
        CHECK_THAT( 0., WithinRel( integrator( xLeft, xLeft, yLeft, yLeft, threshold ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "coulomb integration function" ) {

    WHEN( "integrating an interval" ) {

      THEN( "the integration is performed correctly" ) {

        double xLeft = 2.0;
        double xRight = 7.0;
        double yLeft = 10.0;
        double yRight = 30.0;
        double threshold = 0.3;

        // different x values
        CHECK_THAT( 116.47154112769871, WithinRel( integration::coulomb( xLeft, xRight, yLeft, yRight, threshold ), 1e-8 ) );
        CHECK_THAT( 41.94080794793308, WithinRel( integration::coulomb( 2.4, 4.5, 13.40080679, 24.91047597, threshold ), 1e-8 ) );

        // equal x values
        CHECK_THAT( 0., WithinRel( integration::coulomb( xLeft, xLeft, yLeft, yRight, threshold ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

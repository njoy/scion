// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/CoulombPenetrability.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
using CoulombPenetrability = integration::CoulombPenetrability;

SCENARIO( "CoulombPenetrability" ) {

  GIVEN( "CoulombPenetrability integration object" ) {

    WHEN( "integrating an interval with threshold = 0.3" ) {

      double xLeft = 2.0;
      double xRight = 7.0;
      double yLeft = 10.0;
      double yRight = 30.0;
      double threshold = 0.3;

      CoulombPenetrability integrator{};


      THEN( "the integration is performed correctly" ) {

      
        CHECK_THAT( 116.47154112769871, WithinRel( integrator.integrate( xLeft, xRight, yLeft, yRight, threshold ), 1e-8 ) );

        // different x values
        CHECK_THAT( 41.94080794793308, WithinRel( integrator.integrate( 2.4, 4.5, 13.40080679, 24.91047597, threshold ), 1e-8 ) );

        // equal x values
        CHECK_THAT( 0., WithinRel( integrator( xLeft, xLeft, yLeft, yLeft, threshold ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

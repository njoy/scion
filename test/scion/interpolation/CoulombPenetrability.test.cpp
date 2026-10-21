// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/interpolation/CoulombPenetrability.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "CoulombPenetrability" ) {

  GIVEN( "CoulombPenetrability interpolation object" ) {

    WHEN( "interpolating an x,y interval with threshold = 0.3" ) {

      interpolation::CoulombPenetrability interpolator{};

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 2.0;
        double xRight = 7.0;
        double yLeft = 10.0;
        double yRight = 30.0;
        double threshold = 0.3;

        CHECK_THAT( yLeft , WithinRel( interpolator( 2.0, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( 5.413649473508178, WithinRel( interpolator( 1.5, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( 26.437218001252052 , WithinRel( interpolator( 5.0, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( yRight, WithinRel( interpolator( xRight, xLeft, xRight, yLeft, yRight, threshold ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "coulomb interpolation function" ) {

    WHEN( "interpolating an x,y interval" ) {

      THEN( "the interpolation is performed correctly" ) {

        double xLeft = 2.0;
        double xRight = 7.0;
        double yLeft = 10.0;
        double yRight = 30.0;
        double threshold = 0.3;

        CHECK_THAT( yLeft , WithinRel( interpolation::coulomb( 2.0, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( 5.413649473508178, WithinRel( interpolation::coulomb( 1.5, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( 26.437218001252052 , WithinRel( interpolation::coulomb( 5.0, xLeft, xRight, yLeft, yRight, threshold ) ) );
        CHECK_THAT( yRight, WithinRel( interpolation::coulomb( xRight, xLeft, xRight, yLeft, yRight, threshold ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

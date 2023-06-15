// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "scion/math/compare.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "compare" ) {

  GIVEN( "isClose" ) {

    WHEN( "values are compared" ) {

      THEN( "the values are compared correctly" ) {

        CHECK( false == math::isClose( 1., 2. ) );
        CHECK( true == math::isClose( 1., 1.000000000000015 ) );
        CHECK( true == math::isClose( 0.999999999999985, 1.000000000000015 ) );

        CHECK( true == math::isClose( 4.9303807e-32, 4.930381e-32, 1e-4 ) );
        CHECK( true == math::isClose( 4.9303807e-32, 4.9309825e-32, 1e-4 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "isCloseToZero" ) {

    WHEN( "values are compared" ) {

      THEN( "the values are compared correctly" ) {

        CHECK( true == math::isCloseToZero( 0. ) );
        CHECK( false == math::isCloseToZero( 1e-10 ) );
        CHECK( false == math::isCloseToZero( 1e-12 ) );
        CHECK( true == math::isCloseToZero( 1e-20 ) );
        CHECK( true == math::isCloseToZero( 1e-22 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/linearisation/MidpointSplit.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "MidpointSplit" ) {

  GIVEN( "the default split" ) {

    linearisation::MidpointSplit< double > chunk;

    WHEN( "panels are split" ) {

      THEN( "the correct value is returned" ) {

        CHECK( 1. == Approx( chunk( 0., 2. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

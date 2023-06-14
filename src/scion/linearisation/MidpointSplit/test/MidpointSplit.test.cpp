#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/linearisation/MidpointSplit.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "MidpointSplit" ) {

  GIVEN( "the default split" ) {

    double yLeft = 1.;
    double yRight = 3.;

    linearisation::MidpointSplit< double > chunk;

    WHEN( "panels are split" ) {

      THEN( "the correct value is returned" ) {

        CHECK( 1. == Approx( chunk( 0., 2., yLeft, yRight ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

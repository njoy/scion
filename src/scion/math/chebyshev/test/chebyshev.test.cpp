#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/chebyshev.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "chebyshev" ) {

  GIVEN( "valid values for x" ) {

    std::vector< double > x = { -1.0, -0.5, 0.0, 0.5, 1.0 };

    WHEN( "calculating the value of a Chebyshev polynomial of order n" ) {

      THEN( "the Chebyshev polynomial can be evaluated" ) {

        CHECK(  1.0 == Approx( math::chebyshev( 0, -1.0 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 0, -0.5 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 0,  0.0 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 0,  0.5 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 0,  1.0 ) ) );

        CHECK( -1.0 == Approx( math::chebyshev( 1, -1.0 ) ) );
        CHECK( -0.5 == Approx( math::chebyshev( 1, -0.5 ) ) );
        CHECK(  0.0 == Approx( math::chebyshev( 1,  0.0 ) ) );
        CHECK(  0.5 == Approx( math::chebyshev( 1,  0.5 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 1,  1.0 ) ) );

        CHECK(  1.0 == Approx( math::chebyshev( 2, -1.0 ) ) );
        CHECK( -0.5 == Approx( math::chebyshev( 2, -0.5 ) ) );
        CHECK( -1.0 == Approx( math::chebyshev( 2,  0.0 ) ) );
        CHECK( -0.5 == Approx( math::chebyshev( 2,  0.5 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 2,  1.0 ) ) );

        CHECK( -1.0 == Approx( math::chebyshev( 3, -1.0 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 3, -0.5 ) ) );
        CHECK(  0.0 == Approx( math::chebyshev( 3,  0.0 ) ) );
        CHECK( -1.0 == Approx( math::chebyshev( 3,  0.5 ) ) );
        CHECK(  1.0 == Approx( math::chebyshev( 3,  1.0 ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid values for x" ) {

    WHEN( "calculating the value of a Chebyshev polynomial of order n" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( math::chebyshev( 0, 100. ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

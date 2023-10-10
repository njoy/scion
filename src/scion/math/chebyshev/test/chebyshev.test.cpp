// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/chebyshev.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "chebyshev" ) {

  GIVEN( "valid values for x" ) {

    std::vector< double > x = { -1.0, -0.5, 0.0, 0.5, 1.0 };

    WHEN( "calculating the value of a Chebyshev polynomial of order n" ) {

      THEN( "the Chebyshev polynomial can be evaluated" ) {

        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 0, -1.0 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 0, -0.5 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 0,  0.0 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 0,  0.5 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 0,  1.0 ) ) );

        CHECK_THAT( -1.0, WithinRel( math::chebyshev( 1, -1.0 ) ) );
        CHECK_THAT( -0.5, WithinRel( math::chebyshev( 1, -0.5 ) ) );
        CHECK_THAT(  0.0, WithinRel( math::chebyshev( 1,  0.0 ) ) );
        CHECK_THAT(  0.5, WithinRel( math::chebyshev( 1,  0.5 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 1,  1.0 ) ) );

        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 2, -1.0 ) ) );
        CHECK_THAT( -0.5, WithinRel( math::chebyshev( 2, -0.5 ) ) );
        CHECK_THAT( -1.0, WithinRel( math::chebyshev( 2,  0.0 ) ) );
        CHECK_THAT( -0.5, WithinRel( math::chebyshev( 2,  0.5 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 2,  1.0 ) ) );

        CHECK_THAT( -1.0, WithinRel( math::chebyshev( 3, -1.0 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 3, -0.5 ) ) );
        CHECK_THAT(  0.0, WithinRel( math::chebyshev( 3,  0.0 ) ) );
        CHECK_THAT( -1.0, WithinRel( math::chebyshev( 3,  0.5 ) ) );
        CHECK_THAT(  1.0, WithinRel( math::chebyshev( 3,  1.0 ) ) );
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

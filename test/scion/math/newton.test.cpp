// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "scion/math/newton.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "newton" ) {

  GIVEN( "a function, derivative and root estimate" ) {

    auto functor = [] ( double x ) { return x * x - 1.; };
    auto derivative = [] ( double x ) { return 2. * x; };

    WHEN( "applying the newton-raphson method is applied" ) {

      THEN( "the root can be properly calculated" ) {

        CHECK( 1. == math::newton( 0.5, functor, derivative ) );
        CHECK( 1. == math::newton( 0.7, functor, derivative ) );
        CHECK( 1. == math::newton( 1.2, functor, derivative ) );
        CHECK( 1. == math::newton( 1.5, functor, derivative ) );
        CHECK( 1. == math::newton( 2.0, functor, derivative ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

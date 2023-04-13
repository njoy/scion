#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/IntervalDomain.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "IntervalDomain" ) {

  GIVEN( "valid values for the domain" ) {

    WHEN( "the data is given explicitly" ) {

      double lower = -1.0;
      double upper = +1.0;

      IntervalDomain< double > chunk( lower, upper );

      THEN( "an IntervalDomain can be constructed and members can be tested" ) {

        CHECK( -1.0 == Approx( chunk.lowerLimit() ) );
        CHECK( +1.0 == Approx( chunk.upperLimit() ) );

        CHECK( true == chunk.isInside( -1.0 ) );
        CHECK( true == chunk.isInside( -0.5 ) );
        CHECK( true == chunk.isInside(  0.0 ) );
        CHECK( true == chunk.isInside(  0.5 ) );
        CHECK( true == chunk.isInside(  1.0 ) );

        CHECK( false == chunk.isContained( -1.0 ) );
        CHECK( true == chunk.isContained( -0.5 ) );
        CHECK( true == chunk.isContained(  0.0 ) );
        CHECK( true == chunk.isContained(  0.5 ) );
        CHECK( false == chunk.isContained(  1.0 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid values for the domain" ) {

    WHEN( "the lower limit is larger than the upper limit" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( IntervalDomain< double >( 1.0, -1.0 ) );
      } // THEN
    } // WHEN

    WHEN( "the lower limit is equal to the upper limit" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( IntervalDomain< double >( 1.0, 1.0 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/math/IntervalDomain.hpp"

// other includes

// convenience typedefs
using namespace Catch;
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

        double max = std::numeric_limits<double>::max();
        double min = -max;

        CHECK( false == chunk.isInside( min ) );
        CHECK( true == chunk.isInside( -1.0 ) );
        CHECK( true == chunk.isInside( -0.5 ) );
        CHECK( true == chunk.isInside(  0.0 ) );
        CHECK( true == chunk.isInside(  0.5 ) );
        CHECK( true == chunk.isInside(  1.0 ) );
        CHECK( false == chunk.isInside( max ) );

        CHECK( false == chunk.isContained( min ) );
        CHECK( false == chunk.isContained( -1.0 ) );
        CHECK( true == chunk.isContained( -0.5 ) );
        CHECK( true == chunk.isContained(  0.0 ) );
        CHECK( true == chunk.isContained(  0.5 ) );
        CHECK( false == chunk.isContained(  1.0 ) );
        CHECK( false == chunk.isContained( max ) );
      } // THEN

      THEN( "an IntervalDomain can be compared" ) {

        IntervalDomain< double > same( -1., 1. );
        IntervalDomain< double > different( 0., 1. );

        CHECK( true == ( chunk == same ) );
        CHECK( false == ( chunk == different ) );
        CHECK( false == ( chunk != same ) );
        CHECK( true == ( chunk != different ) );
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

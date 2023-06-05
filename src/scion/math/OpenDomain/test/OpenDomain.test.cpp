#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/OpenDomain.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X > using OpenDomain = math::OpenDomain< X >;

SCENARIO( "OpenDomain" ) {

  GIVEN( "valid values for the domain" ) {

    WHEN( "the data is given explicitly" ) {

      OpenDomain< double > chunk;

      THEN( "an OpenDomain can be constructed and members can be tested" ) {

        double max = std::numeric_limits<double>::max();
        double min = -max;

        CHECK( true == chunk.isInside( min ) );
        CHECK( true == chunk.isInside( -1.0 ) );
        CHECK( true == chunk.isInside( -0.5 ) );
        CHECK( true == chunk.isInside(  0.0 ) );
        CHECK( true == chunk.isInside(  0.5 ) );
        CHECK( true == chunk.isInside(  1.0 ) );
        CHECK( true == chunk.isInside( max ) );

        CHECK( true == chunk.isInside( min ) );
        CHECK( true == chunk.isContained( -1.0 ) );
        CHECK( true == chunk.isContained( -0.5 ) );
        CHECK( true == chunk.isContained(  0.0 ) );
        CHECK( true == chunk.isContained(  0.5 ) );
        CHECK( true == chunk.isContained(  1.0 ) );
        CHECK( true == chunk.isInside( max ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
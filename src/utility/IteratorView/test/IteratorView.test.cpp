#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "utility/IteratorView.hpp"

// other includes

// convenience typedefs
using namespace njoy::utility;

SCENARIO( "IteratorView" ) {

  GIVEN( "a container with values" ) {

    std::vector< int > values = { -2, -1, 0, 1, 2 };

    WHEN( "when iterators are used" ) {

      IteratorView< std::vector< int >::iterator > chunk( values.begin(), values.end() );

      THEN( "an IteratorView can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.size() );
        CHECK( false == chunk.empty() );

        CHECK( -2 == chunk[0] );
        CHECK( -1 == chunk[1] );
        CHECK(  0 == chunk[2] );
        CHECK(  1 == chunk[3] );
        CHECK(  2 == chunk[4] );

        CHECK( -2 == chunk.front() );
        CHECK(  2 == chunk.back() );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

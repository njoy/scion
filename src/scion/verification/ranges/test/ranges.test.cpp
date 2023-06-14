#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "scion/verification/ranges.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "verification ranges" ) {

  GIVEN( "various containers" ) {

    std::vector< double > empty = {};
    std::vector< double > size1 = { 1. };
    std::vector< double > size2 = { 1., 2. };
    std::vector< double > sorted = { 1., 2., 3. };
    std::vector< double > unsorted = { 3., 2., 1. };
    std::vector< double > unique = { 1., 2., 3. };
    std::vector< double > notunique = { 1., 2., 2., 3. };

    WHEN( "the verification functions are called" ) {

      THEN( "the right result is returned" ) {

        CHECK( true == verification::isSameSize( size1, size1 ) );
        CHECK( false == verification::isSameSize( size1, size2 ) );
        CHECK( true == verification::isSameSize( sorted, unsorted ) );
        CHECK( false == verification::isSameSize( sorted, notunique ) );

        CHECK( true == verification::isAtLeastOfSize( size1, 1 ) );
        CHECK( false == verification::isAtLeastOfSize( size1, 2 ) );
        CHECK( true == verification::isAtLeastOfSize( size2, 1 ) );
        CHECK( true == verification::isAtLeastOfSize( size2, 2 ) );

        CHECK( true == verification::isEmpty( empty ) );
        CHECK( false == verification::isEmpty( size1 ) );

        CHECK( true == verification::isSorted( empty ) );
        CHECK( true == verification::isSorted( size1 ) );
        CHECK( true == verification::isSorted( sorted ) );
        CHECK( false == verification::isSorted( unsorted ) );

        CHECK( true == verification::isUnique( empty ) );
        CHECK( true == verification::isUnique( size1 ) );
        CHECK( true == verification::isUnique( unique ) );
        CHECK( false == verification::isUnique( notunique ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

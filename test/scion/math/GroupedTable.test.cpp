// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/GroupedTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename values >
using GroupedTable = math::GroupedTable< X, values >;

SCENARIO( "GroupedTable" ) {

  GIVEN( "tabulated double x,y data" ) {

    std::vector< double > boundaries = { 0., 10., 25., 32. };
    std::vector< double > values = { 34., 35., 36. };

    WHEN( " the ref is given as a reference_wrapper ") {

      GroupedTable< double, double > chunk( boundaries, values );

      THEN( "a GroupedTable can be constructed and members can be tested" ) {

        CHECK( chunk.values().size() == 3 );
        CHECK( chunk.boundaries().size() == 4 );
        CHECK( chunk.numberGroups() == 3 );

        for ( unsigned int i = 0; i < chunk.numberGroups(); i++ ) {

          CHECK_THAT( chunk.values()[i], WithinRel( values[i] ) );
        }

        for ( unsigned int i = 0; i <= chunk.numberGroups(); i++ ) {

          CHECK_THAT( chunk.boundaries()[i], WithinRel( boundaries[i] ) );
        }
      } // THEN


      THEN( "arithmetic operations can be performed" ) {

        GroupedTable< double, double > result( { 0., 32. }, { 0. } );
        GroupedTable< double, double > other( { 0., 10., 25., 32. }, { 1., 2., 3. } );
        GroupedTable< double, double > different( { 0., 15., 30., 32. }, { 1., 2., 3. } );

        chunk += 2.;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 36., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 37., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 38., WithinRel( chunk.values()[2] ) );

        chunk -= 2.;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 34., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 35., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 36., WithinRel( chunk.values()[2] ) );

        chunk *= 2.;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 68., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 70., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 72., WithinRel( chunk.values()[2] ) );

        chunk /= 2.;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 34., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 35., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 36., WithinRel( chunk.values()[2] ) );

        result = -chunk;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( -34., WithinRel( result.values()[0] ) );
        CHECK_THAT( -35., WithinRel( result.values()[1] ) );
        CHECK_THAT( -36., WithinRel( result.values()[2] ) );

        result = chunk + 2.;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 36., WithinRel( result.values()[0] ) );
        CHECK_THAT( 37., WithinRel( result.values()[1] ) );
        CHECK_THAT( 38., WithinRel( result.values()[2] ) );

        result = 2. + chunk;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 36., WithinRel( result.values()[0] ) );
        CHECK_THAT( 37., WithinRel( result.values()[1] ) );
        CHECK_THAT( 38., WithinRel( result.values()[2] ) );

        result = chunk - 2.;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 32., WithinRel( result.values()[0] ) );
        CHECK_THAT( 33., WithinRel( result.values()[1] ) );
        CHECK_THAT( 34., WithinRel( result.values()[2] ) );

        result = 2. - chunk;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( -32., WithinRel( result.values()[0] ) );
        CHECK_THAT( -33., WithinRel( result.values()[1] ) );
        CHECK_THAT( -34., WithinRel( result.values()[2] ) );

        result = chunk * 2.;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 68., WithinRel( result.values()[0] ) );
        CHECK_THAT( 70., WithinRel( result.values()[1] ) );
        CHECK_THAT( 72., WithinRel( result.values()[2] ) );

        result = 2. * chunk;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 68., WithinRel( result.values()[0] ) );
        CHECK_THAT( 70., WithinRel( result.values()[1] ) );
        CHECK_THAT( 72., WithinRel( result.values()[2] ) );

        result = chunk / 2;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 17. , WithinRel( result.values()[0] ) );
        CHECK_THAT( 17.5, WithinRel( result.values()[1] ) );
        CHECK_THAT( 18. , WithinRel( result.values()[2] ) );

        chunk += other;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 35., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 37., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 39., WithinRel( chunk.values()[2] ) );

        chunk -= other;

        CHECK( 3 == chunk.numberGroups() );
        CHECK( 3 == chunk.values().size() );
        CHECK( 4 == chunk.boundaries().size() );
        CHECK_THAT(  0., WithinRel( chunk.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( chunk.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( chunk.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( chunk.boundaries()[3] ) );
        CHECK_THAT( 34., WithinRel( chunk.values()[0] ) );
        CHECK_THAT( 35., WithinRel( chunk.values()[1] ) );
        CHECK_THAT( 36., WithinRel( chunk.values()[2] ) );

        result = chunk + other;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 35., WithinRel( result.values()[0] ) );
        CHECK_THAT( 37., WithinRel( result.values()[1] ) );
        CHECK_THAT( 39., WithinRel( result.values()[2] ) );

        result = chunk - other;

        CHECK( 3 == result.numberGroups() );
        CHECK( 3 == result.values().size() );
        CHECK( 4 == result.boundaries().size() );
        CHECK_THAT(  0., WithinRel( result.boundaries()[0] ) );
        CHECK_THAT( 10., WithinRel( result.boundaries()[1] ) );
        CHECK_THAT( 25., WithinRel( result.boundaries()[2] ) );
        CHECK_THAT( 32., WithinRel( result.boundaries()[3] ) );
        CHECK_THAT( 33., WithinRel( result.values()[0] ) );
        CHECK_THAT( 33., WithinRel( result.values()[1] ) );
        CHECK_THAT( 33., WithinRel( result.values()[2] ) );

        CHECK_THROWS( chunk += different );
        CHECK_THROWS( chunk -= different );
        CHECK_THROWS( result = chunk + different );
        CHECK_THROWS( result = chunk - different );
      } // THEN
    } // WHEN

    WHEN( "bad values are given" ) {

      std::vector< double > outOfOrder{ 1., 2., 1.5, 6. };
      std::vector< double > notUnique{ 1., 3., 3., 5. };
      std::vector< double > notEnough{ 1. };
      std::vector< double > wrongSize{ 1., 2. };

      THEN( "exceptions are thrown" ) {

        CHECK_THROWS( GroupedTable< double, double >( outOfOrder, values ) );
        CHECK_THROWS( GroupedTable< double, double >( notUnique, values ) );
        CHECK_THROWS( GroupedTable< double, double >( notEnough, values ) );
        CHECK_THROWS( GroupedTable< double, double >( wrongSize, values ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

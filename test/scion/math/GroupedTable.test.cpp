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

      GroupedTable< double, double > table( boundaries, values );

      THEN( "a GroupedTable can be constructed and members can be tested" ) {

        CHECK( table.values().size() == 3 );
        CHECK( table.boundaries().size() == 4 );
        CHECK( table.numberGroups() == 3 );

        for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

          CHECK_THAT( table.values()[i], WithinRel( values[i] ) );
        }

        for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

          CHECK_THAT( table.boundaries()[i], WithinRel( boundaries[i] ) );
        }
      } // then

      THEN( "a GroupedTable can be multiplied" ) {

        GroupedTable< double, double > table( boundaries, values );
        GroupedTable< double, double > changed = 2. * table;

        CHECK( changed.values().size() == 3 );
        CHECK( changed.boundaries().size() == 4 );
        CHECK( changed.numberGroups() == 3 );

        for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

            CHECK_THAT( changed.values()[i], WithinRel( 2. * values[i] ) );
        }

        for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

            CHECK_THAT( changed.boundaries()[i], WithinRel( boundaries[i] ) );
        }

        GroupedTable< double, double > changedBack = changed / 2.;

        CHECK( changedBack.values().size() == 3 );
        CHECK( changedBack.boundaries().size() == 4 );
        CHECK( changedBack.numberGroups() == 3 );

        for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

            CHECK_THAT( changedBack.values()[i], WithinRel( values[i] ) );
        }

        for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

            CHECK_THAT( changedBack.boundaries()[i], WithinRel( boundaries[i] ) );
        }

        CHECK( changedBack == table );
        CHECK( changed != table );
      } // then
    } // when

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
      } // then
    } // when
  } // given
} // scenario

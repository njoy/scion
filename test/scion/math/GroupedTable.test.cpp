// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/GroupedTable.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y >
using GroupedTable = math::GroupedTable< X, Y >;

SCENARIO( "GroupedTable" ) {

    GIVEN( "tabulated double x,y data" ) {

        std::vector< double > bounds = { 0., 10., 25., 32. };
        std::vector< double > y = { 34., 35., 36. };

        WHEN( " the ref is given as a reference_wrapper ") {


            GroupedTable< double, double > table( bounds, y );

            THEN( "a GroupedTable can be constructed and members can be tested" ) {

                CHECK( table.values().size() == 3 );
                CHECK( table.bounds().size() == 4 );
                CHECK( table.numberGroups() == 3 );

                for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

                    CHECK_THAT( table.values()[i], WithinRel( y[i] ) );
                }

                for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

                    CHECK_THAT( table.bounds()[i], WithinRel( bounds[i] ) );
                }

            } // then

            THEN( "a GroupedTable can be multiplied" ) {

                GroupedTable< double, double > table( bounds, y );
                GroupedTable< double, double > changed = 2. * table;

                CHECK( changed.values().size() == 3 );
                CHECK( changed.bounds().size() == 4 );
                CHECK( changed.numberGroups() == 3 );

                for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

                    CHECK_THAT( changed.values()[i], WithinRel( 2. * y[i] ) );
                }

                for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

                    CHECK_THAT( changed.bounds()[i], WithinRel( bounds[i] ) );
                }

                
                GroupedTable< double, double > changedBack = changed / 2.;

                CHECK( changedBack.values().size() == 3 );
                CHECK( changedBack.bounds().size() == 4 );
                CHECK( changedBack.numberGroups() == 3 );

                for ( unsigned int i = 0; i < table.numberGroups(); i++ ) {

                    CHECK_THAT( changedBack.values()[i], WithinRel( y[i] ) );
                }

                for ( unsigned int i = 0; i <= table.numberGroups(); i++ ) {

                    CHECK_THAT( changedBack.bounds()[i], WithinRel( bounds[i] ) );
                }

                CHECK( changedBack == table );
                CHECK( changed != table );

            } // then
        }  // when

        WHEN( "bad values are given" ) {
            
            std::vector< double > outOfOrder{ 1., 2., 1.5, 6. };
            std::vector< double > notUnique{ 1., 3., 3., 5. };
            std::vector< double > notEnough{ 1. };
            std::vector< double > wrongSize{ 1., 2. };

            THEN( "exceptions are thrown" ) {

                CHECK_THROWS( GroupedTable< double, double >( outOfOrder, y ) );
                CHECK_THROWS( GroupedTable< double, double >( notUnique, y ) );
                CHECK_THROWS( GroupedTable< double, double >( notEnough, y ) );
                CHECK_THROWS( GroupedTable< double, double >( wrongSize, y ) );
            } // then
        } // when

    } // given
} // scenario

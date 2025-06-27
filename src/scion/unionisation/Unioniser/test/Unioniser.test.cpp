// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/unionisation/Unioniser.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "unionisation grids" ) {

  GIVEN( "various grids" ) {

    std::vector< double > grid1 = { 1., 2., 3., 4. };
    std::vector< double > grid2 = { 1., 1.5, 2., 2.5, 3., 3.5, 4. };
    std::vector< double > grid3 = { 1., 2., 2., 3., 4. };
    std::vector< double > grid4 = { 1., 2., 3., 3., 4. };
    std::vector< double > grid5 = { 1., 2., 2., 3., 3., 4. };
    std::vector< double > grid6 = { 1., 2., 3. };

    unionisation::Unioniser< std::vector< double > > unioniser;

    WHEN( "the grids are unionised" ) {

      THEN( "the right result is returned" ) {

        // same grid => no change
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid1 );
        std::vector< double > grid = unioniser.unionise();

        CHECK( 4 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 4., WithinRel( grid[3] ) );

        // different grids with a few common points but no jumps
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid2 );
        grid = unioniser.unionise();

        CHECK( 7 == grid.size() );
        CHECK_THAT( 1. , WithinRel( grid[0] ) );
        CHECK_THAT( 1.5, WithinRel( grid[1] ) );
        CHECK_THAT( 2. , WithinRel( grid[2] ) );
        CHECK_THAT( 2.5, WithinRel( grid[3] ) );
        CHECK_THAT( 3. , WithinRel( grid[4] ) );
        CHECK_THAT( 3.5, WithinRel( grid[5] ) );
        CHECK_THAT( 4. , WithinRel( grid[6] ) );

        // different grids with a few common points and jumps in the first one
        unioniser.addGrid( grid3 );
        unioniser.addGrid( grid1 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        // different grids with a few common points and jumps in the second one
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid3 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        // different grids with a few common points and jumps in the both but
        // those jumps are not the same
        unioniser.addGrid( grid3 );
        unioniser.addGrid( grid4 );
        grid = unioniser.unionise();

        CHECK( 6 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 3., WithinRel( grid[4] ) );
        CHECK_THAT( 4., WithinRel( grid[5] ) );

        // different grids with a few common points and jumps in both and
        // some jumps are the same
        unioniser.addGrid( grid4 );
        unioniser.addGrid( grid5 );
        grid = unioniser.unionise();

        CHECK( 6 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 3., WithinRel( grid[4] ) );
        CHECK_THAT( 4., WithinRel( grid[5] ) );

        // different grids with different end points (no duplicate end point)
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid6 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        // different grids with different end points (no duplicate end point in
        // other grid)
        unioniser.addGrid( grid6 );
        unioniser.addGrid( grid1 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        // different grids with different end points (duplicate end point in
        // other grid)
        unioniser.addGrid( grid4 );
        unioniser.addGrid( grid6 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        // different grids with different end points (duplicate end point in
        // other grid)
        unioniser.addGrid( grid6 );
        unioniser.addGrid( grid4 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

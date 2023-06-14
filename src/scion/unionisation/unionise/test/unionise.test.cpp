#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/unionisation/unionise.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;

SCENARIO( "unionisation of two grids" ) {

  GIVEN( "various grids" ) {

    std::vector< double > grid1 = { 1., 2., 3., 4. };
    std::vector< double > grid2 = { 1., 1.5, 2., 2.5, 3., 3.5, 4. };
    std::vector< double > grid3 = { 1., 2., 2., 3., 4. };
    std::vector< double > grid4 = { 1., 2., 3., 3., 4. };
    std::vector< double > grid5 = { 1., 2., 2., 3., 3., 4. };

    WHEN( "the grids are unionised" ) {

      THEN( "the right result is returned" ) {

        std::vector< double > grid;

        // same grid => no change
        grid = unionisation::unionise( grid1, grid1 );

        CHECK( 4 == grid.size() );
        CHECK( 1. == Approx( grid[0] ) );
        CHECK( 2. == Approx( grid[1] ) );
        CHECK( 3. == Approx( grid[2] ) );
        CHECK( 4. == Approx( grid[3] ) );

        // different grids with a few common points but no jumps
        grid = unionisation::unionise( grid1, grid2 );

        CHECK( 7 == grid.size() );
        CHECK( 1.  == Approx( grid[0] ) );
        CHECK( 1.5 == Approx( grid[1] ) );
        CHECK( 2.  == Approx( grid[2] ) );
        CHECK( 2.5 == Approx( grid[3] ) );
        CHECK( 3.  == Approx( grid[4] ) );
        CHECK( 3.5 == Approx( grid[5] ) );
        CHECK( 4.  == Approx( grid[6] ) );

        // different grids with a few common points and jumps in the first one
        grid = unionisation::unionise( grid3, grid1 );

        CHECK( 5 == grid.size() );
        CHECK( 1. == Approx( grid[0] ) );
        CHECK( 2. == Approx( grid[1] ) );
        CHECK( 2. == Approx( grid[2] ) );
        CHECK( 3. == Approx( grid[3] ) );
        CHECK( 4. == Approx( grid[4] ) );

        // different grids with a few common points and jumps in the second one
        grid = unionisation::unionise( grid1, grid3 );

        CHECK( 5 == grid.size() );
        CHECK( 1. == Approx( grid[0] ) );
        CHECK( 2. == Approx( grid[1] ) );
        CHECK( 2. == Approx( grid[2] ) );
        CHECK( 3. == Approx( grid[3] ) );
        CHECK( 4. == Approx( grid[4] ) );

        // different grids with a few common points and jumps in the both but
        // those jumps are not the same
        grid = unionisation::unionise( grid3, grid4 );

        CHECK( 6 == grid.size() );
        CHECK( 1. == Approx( grid[0] ) );
        CHECK( 2. == Approx( grid[1] ) );
        CHECK( 2. == Approx( grid[2] ) );
        CHECK( 3. == Approx( grid[3] ) );
        CHECK( 3. == Approx( grid[4] ) );
        CHECK( 4. == Approx( grid[5] ) );

        // different grids with a few common points and jumps in both and
        // some jumps are the same
        grid = unionisation::unionise( grid4, grid5 );

        CHECK( 6 == grid.size() );
        CHECK( 1. == Approx( grid[0] ) );
        CHECK( 2. == Approx( grid[1] ) );
        CHECK( 2. == Approx( grid[2] ) );
        CHECK( 3. == Approx( grid[3] ) );
        CHECK( 3. == Approx( grid[4] ) );
        CHECK( 4. == Approx( grid[5] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/unionisation/Unioniser.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
using namespace njoy::scion::interpolation;

SCENARIO( "unionisation grids" ) {

  GIVEN( "various grids" ) {

    std::vector< double > grid1 = { 1., 2., 3., 4. };
    std::vector< double > grid2 = { 1., 1.5, 2., 2.5, 3., 3.5, 4. };
    std::vector< double > grid3 = { 1., 2., 2., 3., 4. };
    std::vector< double > grid4 = { 1., 2., 3., 3., 4. };
    std::vector< double > grid5 = { 1., 2., 2., 3., 3., 4. };
    std::vector< double > grid6 = { 1., 2., 3. };
    std::vector< double > grid7 = { 2., 3., 4. };
    std::vector< double > grid8 = { 2., 3. };
    std::vector< double > grid9 = { 1.5, 2.5, 3.5 };

    std::vector< double > values1 = { 4., 3., 2., 1. };
    std::vector< double > values2 = { 4., 3.5, 3., 2.5, 2., 1.5, 1. };
    std::vector< double > values3 = { 4., 3., 4., 3., 2. };
    std::vector< double > values4 = { 4., 3., 2., 3., 2. };
    std::vector< double > values5 = { 4., 3., 4., 3., 4., 3. };
    std::vector< double > values6 = { 4., 3., 2. };
    std::vector< double > values7 = { 4., 3., 2. };
    std::vector< double > values8 = { 4., 3. };
    std::vector< double > values9 = { 4., 3., 2. };

    std::vector< std::size_t > boundaries1 = { 2, 3 };
    std::vector< std::size_t > boundaries2 = { 6 };
    std::vector< std::size_t > boundaries3 = { 1, 4 };
    std::vector< std::size_t > boundaries4 = { 2, 4 };
    std::vector< std::size_t > boundaries5 = { 1, 3, 5 };
    std::vector< std::size_t > boundaries6 = { 2 };
    std::vector< std::size_t > boundaries7 = { 2 };
    std::vector< std::size_t > boundaries8 = { 1 };
    std::vector< std::size_t > boundaries9 = { 2 };

    std::vector< InterpolationType > interpolants1 = { InterpolationType::Histogram, InterpolationType::LinearLinear };
    std::vector< InterpolationType > interpolants2 = { InterpolationType::LinearLinear };
    std::vector< InterpolationType > interpolants3 = { InterpolationType::LinearLinear, InterpolationType::LinearLinear };
    std::vector< InterpolationType > interpolants4 = { InterpolationType::LinearLinear, InterpolationType::LinearLinear };
    std::vector< InterpolationType > interpolants5 = { InterpolationType::LinearLinear, InterpolationType::Histogram, InterpolationType::LinearLinear };
    std::vector< InterpolationType > interpolants6 = { InterpolationType::Histogram };
    std::vector< InterpolationType > interpolants7 = { InterpolationType::Histogram };
    std::vector< InterpolationType > interpolants8 = { InterpolationType::Histogram };
    std::vector< InterpolationType > interpolants9 = { InterpolationType::LinearLinear };

    unionisation::Unioniser< std::vector< double > > unioniser;

    WHEN( "the grids are unionised" ) {

      THEN( "the right grid is returned, tables can be reevaluated and updated "
            "boundaries and interpolants can be retrieved" ) {

        // same grid => no change
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid1 );
        std::vector< double > grid = unioniser.unionise();

        CHECK( 4 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 4., WithinRel( grid[3] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( false == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( false == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        std::vector< double > y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 4 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 1., WithinRel( y[3] ) );

        y = unioniser.evaluate( grid1, values1 ); // this assumes lin-lin across the grid

        CHECK( 4 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 1., WithinRel( y[3] ) );

        // different grids with a few common points but no jumps
        unioniser.clear();
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

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( true  == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( false == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( false == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 7 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 4. , WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2. , WithinRel( y[4] ) );
        CHECK_THAT( 1.5, WithinRel( y[5] ) );
        CHECK_THAT( 1. , WithinRel( y[6] ) );

        y = unioniser.evaluate( grid1, values1 ); // this assumes lin-lin across the grid

        CHECK( 7 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 2.5, WithinRel( y[3] ) );
        CHECK_THAT( 2. , WithinRel( y[4] ) );
        CHECK_THAT( 1.5, WithinRel( y[5] ) );
        CHECK_THAT( 1. , WithinRel( y[6] ) );

        y = unioniser.evaluate( grid2, values2, boundaries2, interpolants2 );

        CHECK( 7 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 2.5, WithinRel( y[3] ) );
        CHECK_THAT( 2. , WithinRel( y[4] ) );
        CHECK_THAT( 1.5, WithinRel( y[5] ) );
        CHECK_THAT( 1. , WithinRel( y[6] ) );

        y = unioniser.evaluate( grid2, values2 ); // this assumes lin-lin across the grid, so same as above

        CHECK( 7 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 2.5, WithinRel( y[3] ) );
        CHECK_THAT( 2. , WithinRel( y[4] ) );
        CHECK_THAT( 1.5, WithinRel( y[5] ) );
        CHECK_THAT( 1. , WithinRel( y[6] ) );

        // different grids with a few common points and jumps in the first one
        unioniser.clear();
        unioniser.addGrid( grid3 );
        unioniser.addGrid( grid1 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( true  == unioniser.isComptatible( grid3 ) );
        CHECK( false == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( false == unioniser.isComptatible( grid6 ) );
        CHECK( true  == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid3, values3, boundaries3, interpolants3 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid3, values3 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        // different grids with a few common points and jumps in the second one
        unioniser.clear();
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid3 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 2., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( true  == unioniser.isComptatible( grid3 ) );
        CHECK( false == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( false == unioniser.isComptatible( grid6 ) );
        CHECK( true  == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid3, values3, boundaries3, interpolants3 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid3, values3 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        // different grids with a few common points and jumps in the both but
        // those jumps are not the same
        unioniser.clear();
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

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( true  == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( true  == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( true  == unioniser.isComptatible( grid7 ) );
        CHECK( true  == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid3, values3, boundaries3, interpolants3 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid3, values3 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid4, values4, boundaries4, interpolants4 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid4, values4 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        // different grids with a few common points and jumps in both and
        // some jumps are the same
        unioniser.clear();
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

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( true  == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( true  == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( true  == unioniser.isComptatible( grid7 ) );
        CHECK( true  == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid4, values4, boundaries4, interpolants4 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid4, values4 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 3., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 3., WithinRel( y[4] ) );
        CHECK_THAT( 2., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid5, values5, boundaries5, interpolants5 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 4., WithinRel( y[4] ) );
        CHECK_THAT( 3., WithinRel( y[5] ) );

        y = unioniser.evaluate( grid5, values5 );

        CHECK( 6 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 4., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 4., WithinRel( y[4] ) );
        CHECK_THAT( 3., WithinRel( y[5] ) );

        // different grids with different end points (no duplicate end point)
        unioniser.clear();
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid6 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6, boundaries6, interpolants6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        // different grids with different end points (no duplicate end point in
        // other grid)
        unioniser.clear();
        unioniser.addGrid( grid6 );
        unioniser.addGrid( grid1 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 2., WithinRel( y[3] ) );
        CHECK_THAT( 1., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6, boundaries6, interpolants6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        // different grids with different end points (duplicate end point in
        // other grid)
        unioniser.clear();
        unioniser.addGrid( grid4 );
        unioniser.addGrid( grid6 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid4, values4, boundaries4, interpolants4 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid4, values4 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6, boundaries6, interpolants6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        // different grids with different end points (duplicate end point in
        // other grid)
        unioniser.clear();
        unioniser.addGrid( grid6 );
        unioniser.addGrid( grid4 );
        grid = unioniser.unionise();

        CHECK( 5 == grid.size() );
        CHECK_THAT( 1., WithinRel( grid[0] ) );
        CHECK_THAT( 2., WithinRel( grid[1] ) );
        CHECK_THAT( 3., WithinRel( grid[2] ) );
        CHECK_THAT( 3., WithinRel( grid[3] ) );
        CHECK_THAT( 4., WithinRel( grid[4] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( false == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid4, values4, boundaries4, interpolants4 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid4, values4 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 3., WithinRel( y[3] ) );
        CHECK_THAT( 2., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6, boundaries6, interpolants6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        y = unioniser.evaluate( grid6, values6 );

        CHECK( 5 == y.size() );
        CHECK_THAT( 4., WithinRel( y[0] ) );
        CHECK_THAT( 3., WithinRel( y[1] ) );
        CHECK_THAT( 2., WithinRel( y[2] ) );
        CHECK_THAT( 0., WithinRel( y[3] ) );
        CHECK_THAT( 0., WithinRel( y[4] ) );

        // grids with no points in common
        unioniser.clear();
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid9 );
        grid = unioniser.unionise();

        CHECK( 9 == grid.size() );
        CHECK_THAT( 1. , WithinRel( grid[0] ) );
        CHECK_THAT( 1.5, WithinRel( grid[1] ) );
        CHECK_THAT( 1.5, WithinRel( grid[2] ) );
        CHECK_THAT( 2. , WithinRel( grid[3] ) );
        CHECK_THAT( 2.5, WithinRel( grid[4] ) );
        CHECK_THAT( 3. , WithinRel( grid[5] ) );
        CHECK_THAT( 3.5, WithinRel( grid[6] ) );
        CHECK_THAT( 3.5, WithinRel( grid[7] ) );
        CHECK_THAT( 4. , WithinRel( grid[8] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( true  == unioniser.isComptatible( grid2 ) );
        CHECK( false == unioniser.isComptatible( grid3 ) );
        CHECK( false == unioniser.isComptatible( grid4 ) );
        CHECK( false == unioniser.isComptatible( grid5 ) );
        CHECK( false == unioniser.isComptatible( grid6 ) );
        CHECK( false == unioniser.isComptatible( grid7 ) );
        CHECK( false == unioniser.isComptatible( grid8 ) );
        CHECK( true  == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 4. , WithinRel( y[1] ) );
        CHECK_THAT( 4. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 3. , WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 1.5, WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3.5, WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 1.5, WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid9, values9, boundaries9, interpolants9 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 4. , WithinRel( y[2] ) );
        CHECK_THAT( 3.5, WithinRel( y[3] ) );
        CHECK_THAT( 3. , WithinRel( y[4] ) );
        CHECK_THAT( 2.5, WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid9, values9 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 4. , WithinRel( y[2] ) );
        CHECK_THAT( 3.5, WithinRel( y[3] ) );
        CHECK_THAT( 3. , WithinRel( y[4] ) );
        CHECK_THAT( 2.5, WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        // multiple grids at once
        unioniser.clear();
        unioniser.addGrid( grid1 );
        unioniser.addGrid( grid2 );
        unioniser.addGrid( grid3 );
        unioniser.addGrid( grid4 );
        unioniser.addGrid( grid5 );
        unioniser.addGrid( grid6 );
        unioniser.addGrid( grid7 );
        unioniser.addGrid( grid8 );
        grid = unioniser.unionise();

        CHECK( 9 == grid.size() );
        CHECK_THAT( 1. , WithinRel( grid[0] ) );
        CHECK_THAT( 1.5, WithinRel( grid[1] ) );
        CHECK_THAT( 2. , WithinRel( grid[2] ) );
        CHECK_THAT( 2. , WithinRel( grid[3] ) );
        CHECK_THAT( 2.5, WithinRel( grid[4] ) );
        CHECK_THAT( 3. , WithinRel( grid[5] ) );
        CHECK_THAT( 3. , WithinRel( grid[6] ) );
        CHECK_THAT( 3.5, WithinRel( grid[7] ) );
        CHECK_THAT( 4. , WithinRel( grid[8] ) );

        CHECK( true  == unioniser.isComptatible( grid1 ) );
        CHECK( true  == unioniser.isComptatible( grid2 ) );
        CHECK( true  == unioniser.isComptatible( grid3 ) );
        CHECK( true  == unioniser.isComptatible( grid4 ) );
        CHECK( true  == unioniser.isComptatible( grid5 ) );
        CHECK( true  == unioniser.isComptatible( grid6 ) );
        CHECK( true  == unioniser.isComptatible( grid7 ) );
        CHECK( true  == unioniser.isComptatible( grid8 ) );
        CHECK( false == unioniser.isComptatible( grid9 ) );

        y = unioniser.evaluate( grid1, values1, boundaries1, interpolants1 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 4. , WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 3. , WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid1, values1 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        std::pair< std::vector< std::size_t >, std::vector< InterpolationType> >
        pair = unioniser.updateBoundariesAndInterpolants( grid1, boundaries1, interpolants1 );

        CHECK( 2 == pair.first.size() );
        CHECK( 2 == pair.second.size() );
        CHECK( 5 == pair.first[0] );
        CHECK( 8 == pair.first[1] );
        CHECK( InterpolationType::Histogram == pair.second[0] );
        CHECK( InterpolationType::LinearLinear == pair.second[1] );

        y = unioniser.evaluate( grid2, values2, boundaries2, interpolants2 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid2, values2 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 2. , WithinRel( y[6] ) );
        CHECK_THAT( 1.5, WithinRel( y[7] ) );
        CHECK_THAT( 1. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid2, boundaries2, interpolants2 );

        CHECK( 1 == pair.first.size() );
        CHECK( 1 == pair.second.size() );
        CHECK( 8 == pair.first[0] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );

        y = unioniser.evaluate( grid3, values3, boundaries3, interpolants3 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 3.5, WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 2.5, WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid3, values3 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 3.5, WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 2.5, WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid3, boundaries3, interpolants3 );

        CHECK( 2 == pair.first.size() );
        CHECK( 2 == pair.second.size() );
        CHECK( 2 == pair.first[0] );
        CHECK( 8 == pair.first[1] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );
        CHECK( InterpolationType::LinearLinear == pair.second[1] );

        y = unioniser.evaluate( grid4, values4, boundaries4, interpolants4 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 2.5, WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid4, values4 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 2.5, WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid4, boundaries4, interpolants4 );

        CHECK( 2 == pair.first.size() );
        CHECK( 2 == pair.second.size() );
        CHECK( 5 == pair.first[0] );
        CHECK( 8 == pair.first[1] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );
        CHECK( InterpolationType::LinearLinear == pair.second[1] );

        y = unioniser.evaluate( grid5, values5, boundaries5, interpolants5 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 4. , WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 4. , WithinRel( y[6] ) );
        CHECK_THAT( 3.5, WithinRel( y[7] ) );
        CHECK_THAT( 3. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid5, values5 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 3.5, WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 4. , WithinRel( y[6] ) );
        CHECK_THAT( 3.5, WithinRel( y[7] ) );
        CHECK_THAT( 3. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid5, boundaries5, interpolants5 );

        CHECK( 3 == pair.first.size() );
        CHECK( 3 == pair.second.size() );
        CHECK( 2 == pair.first[0] );
        CHECK( 5 == pair.first[1] );
        CHECK( 8 == pair.first[2] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );
        CHECK( InterpolationType::Histogram == pair.second[1] );
        CHECK( InterpolationType::LinearLinear == pair.second[2] );

        y = unioniser.evaluate( grid6, values6, boundaries6, interpolants6 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 4. , WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 3. , WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 0. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid6, values6 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 4. , WithinRel( y[0] ) );
        CHECK_THAT( 3.5, WithinRel( y[1] ) );
        CHECK_THAT( 3. , WithinRel( y[2] ) );
        CHECK_THAT( 3. , WithinRel( y[3] ) );
        CHECK_THAT( 2.5, WithinRel( y[4] ) );
        CHECK_THAT( 2. , WithinRel( y[5] ) );
        CHECK_THAT( 0. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid6, boundaries6, interpolants6 );

        CHECK( 2 == pair.first.size() );
        CHECK( 2 == pair.second.size() );
        CHECK( 5 == pair.first[0] );
        CHECK( 8 == pair.first[1] );
        CHECK( InterpolationType::Histogram == pair.second[0] );
        CHECK( InterpolationType::LinearLinear == pair.second[1] );

        y = unioniser.evaluate( grid7, values7, boundaries7, interpolants7 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 0. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 4., WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 3. , WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid7, values7 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 0. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 3.5, WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 3. , WithinRel( y[6] ) );
        CHECK_THAT( 2.5, WithinRel( y[7] ) );
        CHECK_THAT( 2. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid7, boundaries7, interpolants7 );

        CHECK( 2 == pair.first.size() );
        CHECK( 2 == pair.second.size() );
        CHECK( 2 == pair.first[0] );
        CHECK( 8 == pair.first[1] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );
        CHECK( InterpolationType::Histogram == pair.second[1] );

        y = unioniser.evaluate( grid8, values8, boundaries8, interpolants8 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 0. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 4. , WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 0. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        y = unioniser.evaluate( grid8, values8 );

        CHECK( 9 == y.size() );
        CHECK_THAT( 0. , WithinRel( y[0] ) );
        CHECK_THAT( 0. , WithinRel( y[1] ) );
        CHECK_THAT( 0. , WithinRel( y[2] ) );
        CHECK_THAT( 4. , WithinRel( y[3] ) );
        CHECK_THAT( 3.5, WithinRel( y[4] ) );
        CHECK_THAT( 3. , WithinRel( y[5] ) );
        CHECK_THAT( 0. , WithinRel( y[6] ) );
        CHECK_THAT( 0. , WithinRel( y[7] ) );
        CHECK_THAT( 0. , WithinRel( y[8] ) );

        pair = unioniser.updateBoundariesAndInterpolants( grid8, boundaries8, interpolants8 );

        CHECK( 3 == pair.first.size() );
        CHECK( 3 == pair.second.size() );
        CHECK( 2 == pair.first[0] );
        CHECK( 5 == pair.first[1] );
        CHECK( 8 == pair.first[2] );
        CHECK( InterpolationType::LinearLinear == pair.second[0] );
        CHECK( InterpolationType::Histogram == pair.second[1] );
        CHECK( InterpolationType::LinearLinear == pair.second[2] );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

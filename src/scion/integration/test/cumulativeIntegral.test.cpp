// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/integration/cumulativeIntegral.hpp"
#include "scion/integration/LinearLinear.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "integrate" ) {

  GIVEN( "tabulated x and y values" ) {

    std::vector< double > x = { 1., 2., 3, 4, 5. };
    std::vector< double > y = { 5., 4., 3, 2, 1. };

    WHEN( "an analytical integrator is applied" ) {

      integration::LinearLinear integrator;

      THEN( "the integration is performed correctly using iterators" ) {

        // over the entire table
        auto xbegin = x.begin() + 1;
        auto ybegin = y.begin() + 1;
        auto result = integration::cumulativeIntegral( 0., xbegin, x.end(), ybegin, integrator );
        CHECK( 5 == result.size() );
        CHECK_THAT(  0. , WithinRel( result[0] ) );
        CHECK_THAT(  4.5, WithinRel( result[1] ) );
        CHECK_THAT(  8. , WithinRel( result[2] ) );
        CHECK_THAT( 10.5, WithinRel( result[3] ) );
        CHECK_THAT( 12. , WithinRel( result[4] ) );

        // over the first 2 panels of the table
        xbegin = x.begin() + 1;
        ybegin = y.begin() + 1;
        result = integration::cumulativeIntegral( 0., xbegin, xbegin + 2, ybegin, integrator );
        CHECK( 3 == result.size() );
        CHECK_THAT(  0. , WithinRel( result[0] ) );
        CHECK_THAT(  4.5, WithinRel( result[1] ) );
        CHECK_THAT(  8. , WithinRel( result[2] ) );

        // over the middle 2 panels of the table
        xbegin = x.begin() + 2;
        ybegin = y.begin() + 2;
        result = integration::cumulativeIntegral( 0., xbegin, xbegin + 2, ybegin, integrator );
        CHECK( 3 == result.size() );
        CHECK_THAT(  0. , WithinRel( result[0] ) );
        CHECK_THAT(  3.5, WithinRel( result[1] ) );
        CHECK_THAT(  6. , WithinRel( result[2] ) );

        // over the last 2 panels of the table
        xbegin = x.begin() + 3;
        ybegin = y.begin() + 3;
        result = integration::cumulativeIntegral( 0., xbegin, x.end(), ybegin, integrator );
        CHECK( 3 == result.size() );
        CHECK_THAT(  0. , WithinRel( result[0] ) );
        CHECK_THAT(  2.5, WithinRel( result[1] ) );
        CHECK_THAT(  4. , WithinRel( result[2] ) );
      } // THEN

      THEN( "the integration is performed correctly using ranges" ) {

        // over the entire table
        auto result = integration::cumulativeIntegral( 0., x, y, integrator );
        CHECK( 5 == result.size() );
        CHECK_THAT(  0. , WithinRel( result[0] ) );
        CHECK_THAT(  4.5, WithinRel( result[1] ) );
        CHECK_THAT(  8. , WithinRel( result[2] ) );
        CHECK_THAT( 10.5, WithinRel( result[3] ) );
        CHECK_THAT( 12. , WithinRel( result[4] ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/horner.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "horner" ) {

  GIVEN( "valid data for a polynomial" ) {

    // polynomial coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    WHEN( "the iterators are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::horner( order0.rbegin(), order0.rend(), 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order1.rbegin(), order1.rend(), 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order2.rbegin(), order2.rend(), 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order3.rbegin(), order3.rend(), 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::horner( order0.rbegin(), order0.rend(), 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::horner( order1.rbegin(), order1.rend(), 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::horner( order2.rbegin(), order2.rend(), 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::horner( order3.rbegin(), order3.rend(), 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::horner( order0.rbegin(), order0.rend(), -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::horner( order1.rbegin(), order1.rend(), -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::horner( order2.rbegin(), order2.rend(), -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::horner( order3.rbegin(), order3.rend(), -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK_THAT(  1., WithinRel( math::horner( order0, 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order1, 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order2, 0. ) ) );
        CHECK_THAT(  1., WithinRel( math::horner( order3, 0. ) ) );

        CHECK_THAT(  1., WithinRel( math::horner( order0, 1. ) ) );
        CHECK_THAT(  3., WithinRel( math::horner( order1, 1. ) ) );
        CHECK_THAT(  6., WithinRel( math::horner( order2, 1. ) ) );
        CHECK_THAT( 10., WithinRel( math::horner( order3, 1. ) ) );

        CHECK_THAT(  1., WithinRel( math::horner( order0, -1. ) ) );
        CHECK_THAT( -1., WithinRel( math::horner( order1, -1. ) ) );
        CHECK_THAT(  2., WithinRel( math::horner( order2, -1. ) ) );
        CHECK_THAT( -2., WithinRel( math::horner( order3, -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

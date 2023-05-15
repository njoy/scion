#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/clenshaw.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;

SCENARIO( "clenshaw" ) {

  GIVEN( "valid data for polynomials" ) {

    // polynomial coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double
                { return x; };
    auto b = [] ( unsigned int k, double x ) -> double
                { return 0.; };

    WHEN( "the iterators are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the polynomials can be evaluated" ) {

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for Legendre polynomials" ) {

    // Legendre coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double {

      return static_cast< double >( 2 * k + 1 ) / static_cast< double >( k + 1 ) * x;
    };
    auto b = [] ( unsigned int k, double x ) -> double {

      return - static_cast< double >( k ) / static_cast< double >( k + 1 );
    };

    WHEN( "the iterators are used" ) {

      THEN( "the Legendre polynomials can be evaluated" ) {

        CHECK(   1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK(   1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );

        CHECK(   1. == Approx( math::clenshawLegendre( order0.rbegin(), order0.rend(), 0. ) ) );
        CHECK(   1. == Approx( math::clenshawLegendre( order1.rbegin(), order1.rend(), 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshawLegendre( order2.rbegin(), order2.rend(), 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshawLegendre( order3.rbegin(), order3.rend(), 0. ) ) );

        CHECK(  1. == Approx( math::clenshawLegendre( order0.rbegin(), order0.rend(), 1. ) ) );
        CHECK(  3. == Approx( math::clenshawLegendre( order1.rbegin(), order1.rend(), 1. ) ) );
        CHECK(  6. == Approx( math::clenshawLegendre( order2.rbegin(), order2.rend(), 1. ) ) );
        CHECK( 10. == Approx( math::clenshawLegendre( order3.rbegin(), order3.rend(), 1. ) ) );

        CHECK(  1. == Approx( math::clenshawLegendre( order0.rbegin(), order0.rend(), -1. ) ) );
        CHECK( -1. == Approx( math::clenshawLegendre( order1.rbegin(), order1.rend(), -1. ) ) );
        CHECK(  2. == Approx( math::clenshawLegendre( order2.rbegin(), order2.rend(), -1. ) ) );
        CHECK( -2. == Approx( math::clenshawLegendre( order3.rbegin(), order3.rend(), -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the Legendre polynomials can be evaluated" ) {

        CHECK(   1. == Approx( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK(   1. == Approx( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );

        CHECK(   1. == Approx( math::clenshawLegendre( order0, 0. ) ) );
        CHECK(   1. == Approx( math::clenshawLegendre( order1, 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshawLegendre( order2, 0. ) ) );
        CHECK( -0.5 == Approx( math::clenshawLegendre( order3, 0. ) ) );

        CHECK(  1. == Approx( math::clenshawLegendre( order0, 1. ) ) );
        CHECK(  3. == Approx( math::clenshawLegendre( order1, 1. ) ) );
        CHECK(  6. == Approx( math::clenshawLegendre( order2, 1. ) ) );
        CHECK( 10. == Approx( math::clenshawLegendre( order3, 1. ) ) );

        CHECK(  1. == Approx( math::clenshawLegendre( order0, -1. ) ) );
        CHECK( -1. == Approx( math::clenshawLegendre( order1, -1. ) ) );
        CHECK(  2. == Approx( math::clenshawLegendre( order2, -1. ) ) );
        CHECK( -2. == Approx( math::clenshawLegendre( order3, -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for Chebyshev polynomials" ) {

    // Chebyshev coefficients (from lower order to higher order)
    std::vector< double > order0 = { 1. };
    std::vector< double > order1 = { 1., 2. };
    std::vector< double > order2 = { 1., 2., 3. };
    std::vector< double > order3 = { 1., 2., 3., 4. };

    auto a = [] ( unsigned int k, double x ) -> double {

      return static_cast< double >( 2 ) * x;
    };
    auto b = [] ( unsigned int k, double x ) -> double {

      return - static_cast< double >( 1 );
    };

    WHEN( "the iterators are used" ) {

      THEN( "the Chebyshev polynomials can be evaluated" ) {

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 0., 0. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 0., 0. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0.rbegin(), order0.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1.rbegin(), order1.rend(), a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2.rbegin(), order2.rend(), a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3.rbegin(), order3.rend(), a, b, 1., -1., -1. ) ) );

        CHECK(   1. == Approx( math::clenshawChebyshev( order0.rbegin(), order0.rend(), 0. ) ) );
        CHECK(   1. == Approx( math::clenshawChebyshev( order1.rbegin(), order1.rend(), 0. ) ) );
        CHECK(  -2. == Approx( math::clenshawChebyshev( order2.rbegin(), order2.rend(), 0. ) ) );
        CHECK(  -2. == Approx( math::clenshawChebyshev( order3.rbegin(), order3.rend(), 0. ) ) );

        CHECK(  1. == Approx( math::clenshawChebyshev( order0.rbegin(), order0.rend(), 1. ) ) );
        CHECK(  3. == Approx( math::clenshawChebyshev( order1.rbegin(), order1.rend(), 1. ) ) );
        CHECK(  6. == Approx( math::clenshawChebyshev( order2.rbegin(), order2.rend(), 1. ) ) );
        CHECK( 10. == Approx( math::clenshawChebyshev( order3.rbegin(), order3.rend(), 1. ) ) );

        CHECK(  1. == Approx( math::clenshawChebyshev( order0.rbegin(), order0.rend(), -1. ) ) );
        CHECK( -1. == Approx( math::clenshawChebyshev( order1.rbegin(), order1.rend(), -1. ) ) );
        CHECK(  2. == Approx( math::clenshawChebyshev( order2.rbegin(), order2.rend(), -1. ) ) );
        CHECK( -2. == Approx( math::clenshawChebyshev( order3.rbegin(), order3.rend(), -1. ) ) );
      } // THEN
    } // WHEN

    WHEN( "the vectors are used" ) {

      THEN( "the Chebyshev polynomials can be evaluated" ) {

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., 0., 0. ) ) );
        CHECK(  1. == Approx( math::clenshaw( order1, a, b, 1., 0., 0. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order2, a, b, 1., 0., 0. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3, a, b, 1., 0., 0. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., 1., 1. ) ) );
        CHECK(  3. == Approx( math::clenshaw( order1, a, b, 1., 1., 1. ) ) );
        CHECK(  6. == Approx( math::clenshaw( order2, a, b, 1., 1., 1. ) ) );
        CHECK( 10. == Approx( math::clenshaw( order3, a, b, 1., 1., 1. ) ) );

        CHECK(  1. == Approx( math::clenshaw( order0, a, b, 1., -1., -1. ) ) );
        CHECK( -1. == Approx( math::clenshaw( order1, a, b, 1., -1., -1. ) ) );
        CHECK(  2. == Approx( math::clenshaw( order2, a, b, 1., -1., -1. ) ) );
        CHECK( -2. == Approx( math::clenshaw( order3, a, b, 1., -1., -1. ) ) );

        CHECK(  1. == Approx( math::clenshawChebyshev( order0, 0. ) ) );
        CHECK(  1. == Approx( math::clenshawChebyshev( order1, 0. ) ) );
        CHECK( -2. == Approx( math::clenshawChebyshev( order2, 0. ) ) );
        CHECK( -2. == Approx( math::clenshawChebyshev( order3, 0. ) ) );

        CHECK(  1. == Approx( math::clenshawChebyshev( order0, 1. ) ) );
        CHECK(  3. == Approx( math::clenshawChebyshev( order1, 1. ) ) );
        CHECK(  6. == Approx( math::clenshawChebyshev( order2, 1. ) ) );
        CHECK( 10. == Approx( math::clenshawChebyshev( order3, 1. ) ) );

        CHECK(  1. == Approx( math::clenshawChebyshev( order0, -1. ) ) );
        CHECK( -1. == Approx( math::clenshawChebyshev( order1, -1. ) ) );
        CHECK(  2. == Approx( math::clenshawChebyshev( order2, -1. ) ) );
        CHECK( -2. == Approx( math::clenshawChebyshev( order3, -1. ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/AnalyticalIntegrator.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X >
using AnalyticalIntegrator = math::AnalyticalIntegrator< X >;

SCENARIO( "AnalyticalIntegrator" ) {

  GIVEN( "valid integration boundaries" ) {

    WHEN( "multiple integration intervals are given" ) {

      std::vector< double > boundaries = { 1., 2., 3., 4. };
      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "an AnalyticalIntegrator can be constructed and members can be tested" ) {

        CHECK( 3 == integrator.numberIntervals() );
        CHECK( 4 == integrator.boundaries().size() );

        CHECK( 1. == integrator.boundaries()[0] );
        CHECK( 2. == integrator.boundaries()[1] );
        CHECK( 3. == integrator.boundaries()[2] );
        CHECK( 4. == integrator.boundaries()[3] );
      }
    }

    WHEN( "a single interval is given" ) {

      double a = 1.;
      double b = 4.;
      AnalyticalIntegrator< double > integrator( a, b );

      THEN( "an AnalyticalIntegrator can be constructed and members can be tested" ) {

        CHECK( 1 == integrator.numberIntervals() );
        CHECK( 2 == integrator.boundaries().size() );

        CHECK( 1. == integrator.boundaries()[0] );
        CHECK( 4. == integrator.boundaries()[1] );
      }
    }
  }

  GIVEN( "tabulated data to be integrated using the call operator" ) {

    std::vector< double > x = { 1., 2., 3., 4. };
    std::vector< double > y = { 4., 3., 2., 1. };
    InterpolationTable< double > table( std::move( x ), std::move( y ) );

    WHEN( "the boundaries are the same as the tabulated x grid" ) {

      std::vector< double > boundaries = { 1., 2., 3., 4. };

      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "the integrals are calculated correctly" ) {

        std::vector< double > result = integrator( table );

        CHECK( 3 == result.size() );
        CHECK_THAT( 3.5, WithinRel( result[0] ) );
        CHECK_THAT( 2.5, WithinRel( result[1] ) );
        CHECK_THAT( 1.5, WithinRel( result[2] ) );

        result = integrator.zerothMoment( table );

        CHECK( 3 == result.size() );
        CHECK_THAT( 3.5, WithinRel( result[0] ) );
        CHECK_THAT( 2.5, WithinRel( result[1] ) );
        CHECK_THAT( 1.5, WithinRel( result[2] ) );

        result = integrator.mean( table );

        CHECK( 3 == result.size() );
        CHECK_THAT( 5. + 1./6., WithinRel( result[0] ) );
        CHECK_THAT( 6. + 1./6., WithinRel( result[1] ) );
        CHECK_THAT( 5. + 1./6., WithinRel( result[2] ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are inside the tabulated x grid" ) {

      std::vector< double > boundaries = { 1.5, 2.5, 3.5 };

      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "the integrals are calculated correctly" ) {

        std::vector< double > result = integrator( table );

        CHECK( 2 == result.size() );
        CHECK_THAT( 3., WithinRel( result[0] ) );
        CHECK_THAT( 2., WithinRel( result[1] ) );

        result = integrator.zerothMoment( table );

        CHECK( 2 == result.size() );
        CHECK_THAT( 3., WithinRel( result[0] ) );
        CHECK_THAT( 2., WithinRel( result[1] ) );

        result = integrator.mean( table );

        CHECK( 2 == result.size() );
        CHECK_THAT( 5. + 11./12., WithinRel( result[0] ) );
        CHECK_THAT( 5. + 11./12., WithinRel( result[1] ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are larger than the tabulated x grid on the left" ) {

      std::vector< double > boundaries = { -1., 0., 1., 2., 3., 4. };

      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "the integrals are calculated correctly" ) {

        std::vector< double > result = integrator( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 0.0, WithinRel( result[0] ) );
        CHECK_THAT( 0.0, WithinRel( result[1] ) );
        CHECK_THAT( 3.5, WithinRel( result[2] ) );
        CHECK_THAT( 2.5, WithinRel( result[3] ) );
        CHECK_THAT( 1.5, WithinRel( result[4] ) );

        result = integrator.zerothMoment( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 0.0, WithinRel( result[0] ) );
        CHECK_THAT( 0.0, WithinRel( result[1] ) );
        CHECK_THAT( 3.5, WithinRel( result[2] ) );
        CHECK_THAT( 2.5, WithinRel( result[3] ) );
        CHECK_THAT( 1.5, WithinRel( result[4] ) );

        result = integrator.mean( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 0.0       , WithinRel( result[0] ) );
        CHECK_THAT( 0.0       , WithinRel( result[1] ) );
        CHECK_THAT( 5. + 1./6., WithinRel( result[2] ) );
        CHECK_THAT( 6. + 1./6., WithinRel( result[3] ) );
        CHECK_THAT( 5. + 1./6., WithinRel( result[4] ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries are larger than the tabulated x grid on the right" ) {

      std::vector< double > boundaries = { 1., 2., 3., 4., 5., 6. };

      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "the integrals are calculated correctly" ) {

        std::vector< double > result = integrator( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 3.5, WithinRel( result[0] ) );
        CHECK_THAT( 2.5, WithinRel( result[1] ) );
        CHECK_THAT( 1.5, WithinRel( result[2] ) );
        CHECK_THAT( 0.0, WithinRel( result[3] ) );
        CHECK_THAT( 0.0, WithinRel( result[4] ) );

        result = integrator.zerothMoment( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 3.5, WithinRel( result[0] ) );
        CHECK_THAT( 2.5, WithinRel( result[1] ) );
        CHECK_THAT( 1.5, WithinRel( result[2] ) );
        CHECK_THAT( 0.0, WithinRel( result[3] ) );
        CHECK_THAT( 0.0, WithinRel( result[4] ) );

        result = integrator.mean( table );

        CHECK( 5 == result.size() );
        CHECK_THAT( 5. + 1./6., WithinRel( result[0] ) );
        CHECK_THAT( 6. + 1./6., WithinRel( result[1] ) );
        CHECK_THAT( 5. + 1./6., WithinRel( result[2] ) );
        CHECK_THAT( 0.0       , WithinRel( result[3] ) );
        CHECK_THAT( 0.0       , WithinRel( result[4] ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries has multiple groups in an interpolation panel" ) {

      std::vector< double > boundaries = { 1., 1.2, 1.4, 1.6, 1.8, 2., 3., 4. };

      AnalyticalIntegrator< double > integrator( std::move( boundaries ) );

      THEN( "the integrals are calculated correctly" ) {

        std::vector< double > result = integrator( table );

        CHECK( 7 == result.size() );
        CHECK_THAT( 0.78, WithinRel( result[0] ) );
        CHECK_THAT( 0.74, WithinRel( result[1] ) );
        CHECK_THAT( 0.7, WithinRel( result[2] ) );
        CHECK_THAT( 0.66, WithinRel( result[3] ) );
        CHECK_THAT( 0.62, WithinRel( result[4] ) );
        CHECK_THAT( 2.5, WithinRel( result[5] ) );
        CHECK_THAT( 1.5, WithinRel( result[6] ) );

        result = integrator.zerothMoment( table );

        CHECK( 7 == result.size() );
        CHECK_THAT( 0.78, WithinRel( result[0] ) );
        CHECK_THAT( 0.74, WithinRel( result[1] ) );
        CHECK_THAT( 0.7, WithinRel( result[2] ) );
        CHECK_THAT( 0.66, WithinRel( result[3] ) );
        CHECK_THAT( 0.62, WithinRel( result[4] ) );
        CHECK_THAT( 2.5, WithinRel( result[5] ) );
        CHECK_THAT( 1.5, WithinRel( result[6] ) );

        result = integrator.mean( table );

        CHECK( 7 == result.size() );
        CHECK_THAT( 5.144 / 6., WithinRel( result[0] ) );
        CHECK_THAT( 5.768 / 6., WithinRel( result[1] ) );
        CHECK_THAT( 6.296 / 6., WithinRel( result[2] ) );
        CHECK_THAT( 6.728 / 6., WithinRel( result[3] ) );
        CHECK_THAT( 7.064 / 6., WithinRel( result[4] ) );
        CHECK_THAT( 6. + 1./6., WithinRel( result[5] ) );
        CHECK_THAT( 5. + 1./6., WithinRel( result[6] ) );

      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

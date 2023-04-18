#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/LegendreSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using LegendreSeries = math::LegendreSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "LegendreSeries" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      std::vector< double > coefficients = { 1., 2., 3., 4. };

      LegendreSeries< double > chunk( std::move( coefficients ) );

      THEN( "a LegendreSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK( 1. == Approx( chunk.coefficients()[0] ) );
        CHECK( 2. == Approx( chunk.coefficients()[1] ) );
        CHECK( 3. == Approx( chunk.coefficients()[2] ) );
        CHECK( 4. == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LegendreSeries can be evaluated" ) {

        CHECK( -0.5 == Approx( chunk.evaluate(  0. ) ) );
        CHECK( 10.0 == Approx( chunk.evaluate(  1. ) ) );
        CHECK( -2.0 == Approx( chunk.evaluate( -1. ) ) );

        CHECK( -0.5 == Approx( chunk(  0. ) ) );
        CHECK( 10.0 == Approx( chunk(  1. ) ) );
        CHECK( -2.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "a LegendreSeries can be differentiated" ) {

        LegendreSeries< double > first = chunk.derivative();
        LegendreSeries< double > second = first.derivative();
        LegendreSeries< double > third = second.derivative();
        LegendreSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK( 6. == Approx( first.coefficients()[0] ) );
        CHECK( 9. == Approx( first.coefficients()[1] ) );
        CHECK( 20. == Approx( first.coefficients()[2] ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( 9. == Approx( second.coefficients()[0] ) );
        CHECK( 60. == Approx( second.coefficients()[1] ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 60. == Approx( third.coefficients()[0] ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK( 0. == Approx( fourth.coefficients()[0] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreSeries< double >( {} ) );
      } // THEN
    } // WHEN

    WHEN( "the x values are outside the domain" ) {

      double max = std::numeric_limits<double>::max();
      double min = -max;

      LegendreSeries< double > chunk( { 1., 2., 3., 4. } );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk( min ) );
        CHECK_THROWS( chunk( -10. ) );
        CHECK_THROWS( chunk(  10. ) );
        CHECK_THROWS( chunk( max ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

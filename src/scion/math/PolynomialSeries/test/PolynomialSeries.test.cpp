#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "scion/math/PolynomialSeries.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using PolynomialSeries = math::PolynomialSeries< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;

SCENARIO( "PolynomialSeries" ) {

  GIVEN( "Legendre coefficients for an expansion" ) {

    WHEN( "the data is given explicitly" ) {

      double lower = -1.;
      double upper = 1.;
      std::vector< double > coefficients = { 1., 2., 3., 4. };

      PolynomialSeries< double > chunk( lower, upper, std::move( coefficients ) );

      THEN( "a PolynomialSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK( 4 == chunk.coefficients().size() );
        CHECK( 1. == Approx( chunk.coefficients()[0] ) );
        CHECK( 2. == Approx( chunk.coefficients()[1] ) );
        CHECK( 3. == Approx( chunk.coefficients()[2] ) );
        CHECK( 4. == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a PolynomialSeries can be evaluated" ) {

        CHECK(  1.0 == Approx( chunk.evaluate(  0. ) ) );
        CHECK( 10.0 == Approx( chunk.evaluate(  1. ) ) );
        CHECK( -2.0 == Approx( chunk.evaluate( -1. ) ) );

        CHECK(  1.0 == Approx( chunk(  0. ) ) );
        CHECK( 10.0 == Approx( chunk(  1. ) ) );
        CHECK( -2.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "a PolynomialSeries can be differentiated" ) {

        PolynomialSeries< double > first = chunk.derivative();
        PolynomialSeries< double > second = first.derivative();
        PolynomialSeries< double > third = second.derivative();
        PolynomialSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK( 2. == Approx( first.coefficients()[0] ) );
        CHECK( 6. == Approx( first.coefficients()[1] ) );
        CHECK( 12. == Approx( first.coefficients()[2] ) );
        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( first.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( 6. == Approx( second.coefficients()[0] ) );
        CHECK( 24. == Approx( second.coefficients()[1] ) );
        domain = std::get< IntervalDomain< double > >( second.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 24. == Approx( third.coefficients()[0] ) );
        domain = std::get< IntervalDomain< double > >( third.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 0 == fourth.order() );
        CHECK( 1 == fourth.coefficients().size() );
        CHECK( 0. == Approx( fourth.coefficients()[0] ) );
        domain = std::get< IntervalDomain< double > >( fourth.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialSeries< double >( {} ) );
      } // THEN
    } // WHEN

    WHEN( "the x values are outside the domain" ) {

      double max = std::numeric_limits<double>::max();
      double min = -max;

      PolynomialSeries< double > chunk( -1., 1., { 1., 2., 3., 4. } );

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( chunk( min ) );
        CHECK_THROWS( chunk( -10. ) );
        CHECK_THROWS( chunk(  10. ) );
        CHECK_THROWS( chunk( max ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

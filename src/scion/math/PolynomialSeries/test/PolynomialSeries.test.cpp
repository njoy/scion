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

      // the 3rd order polynomial was designed to have 3 real roots: 1, 2 and 4

      double lower = -1.;
      double upper = 1.;
      std::vector< double > coefficients = { -8., 14., -7., 1. };

      PolynomialSeries< double > chunk( lower, upper, std::move( coefficients ) );

      THEN( "a PolynomialSeries can be constructed and members can be tested" ) {

        CHECK( 3 == chunk.order() );

        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a PolynomialSeries can be evaluated" ) {

        CHECK(  -8.0 == Approx( chunk(  0. ) ) );
        CHECK(   0.0 == Approx( chunk(  1. ) ) );
        CHECK( -30.0 == Approx( chunk( -1. ) ) );
      } // THEN

      THEN( "a PolynomialSeries can be differentiated" ) {

        PolynomialSeries< double > first = chunk.derivative();
        PolynomialSeries< double > second = first.derivative();
        PolynomialSeries< double > third = second.derivative();
        PolynomialSeries< double > fourth = third.derivative();

        CHECK( 2 == first.order() );
        CHECK( 3 == first.coefficients().size() );
        CHECK(  14. == Approx( first.coefficients()[0] ) );
        CHECK( -14. == Approx( first.coefficients()[1] ) );
        CHECK(   3. == Approx( first.coefficients()[2] ) );
        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( first.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 1 == second.order() );
        CHECK( 2 == second.coefficients().size() );
        CHECK( -14. == Approx( second.coefficients()[0] ) );
        CHECK(   6. == Approx( second.coefficients()[1] ) );
        domain = std::get< IntervalDomain< double > >( second.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );

        CHECK( 0 == third.order() );
        CHECK( 1 == third.coefficients().size() );
        CHECK( 6. == Approx( third.coefficients()[0] ) );
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

      THEN( "a PolynomialSeries can be integrated" ) {

        PolynomialSeries< double > primitive = chunk.primitive();

        CHECK( 4 == primitive.order() );
        CHECK( 5 == primitive.coefficients().size() );
        CHECK(   0. == Approx( primitive.coefficients()[0] ) );
        CHECK(  -8. == Approx( primitive.coefficients()[1] ) );
        CHECK(   7. == Approx( primitive.coefficients()[2] ) );
        CHECK(  -7. / 3. == Approx( primitive.coefficients()[3] ) );
        CHECK(   1. / 4. == Approx( primitive.coefficients()[4] ) );
        IntervalDomain< double > domain = std::get< IntervalDomain< double > >( primitive.domain() );
        CHECK( -1. == Approx( domain.lowerLimit() ) );
        CHECK(  1. == Approx( domain.upperLimit() ) );
      } // THEN

      THEN( "roots can be calculated" ) {

        std::vector< double > roots = chunk.roots();

        CHECK( 3 == roots.size() );
        CHECK( 1.0 == Approx( roots[0] ) );
        CHECK( 2.0 == Approx( roots[1] ) );
        CHECK( 4.0 == Approx( roots[2] ) );

        roots = chunk.roots( -8. );

        CHECK( 1 == roots.size() );
        CHECK(  0.0 == Approx( roots[0] ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        chunk += 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -6. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 3 == chunk.order() );
        CHECK(  4 == chunk.coefficients().size() );
        CHECK( -8. == Approx( chunk.coefficients()[0] ) );
        CHECK( 14. == Approx( chunk.coefficients()[1] ) );
        CHECK( -7. == Approx( chunk.coefficients()[2] ) );
        CHECK(  1. == Approx( chunk.coefficients()[3] ) );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the coefficient vector is empty" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( PolynomialSeries< double >( {} ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

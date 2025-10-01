// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/PolynomialSeriesRatio.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using PolynomialSeries = math::PolynomialSeries< X, Y >;
template < typename X, typename Y = X > using PolynomialSeriesRatio = math::PolynomialSeriesRatio< X, Y >;

SCENARIO( "PolynomialSeriesRatio" ) {

  GIVEN( "coefficients for a numerator and denominator series" ) {

    WHEN( "the data is given explicitly" ) {

      // the 3rd order polynomial was designed to have 3 real roots: 1, 2 and 4

      std::vector< double > numerator = { -8., 14., -7., 1. };
      std::vector< double > denominator = { 3., 0, 5. };

      PolynomialSeriesRatio< double > chunk( std::move( numerator ),
                                             std::move( denominator ) );

      THEN( "a PolynomialSeriesRatio can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );
      } // THEN

      THEN( "a PolynomialSeriesRatio can be evaluated" ) {

        CHECK_THAT(  -8. / 3., WithinRel( chunk(  0. ) ) );
        CHECK_THAT(   0.     , WithinRel( chunk(  1. ) ) );
        CHECK_THAT( -30. / 8., WithinRel( chunk( -1. ) ) );
      } // THEN

      THEN( "a PolynomialSeriesRatio can be derived" ) {

        auto derivative = chunk.derivative();

        CHECK( 5 == derivative.numerator().coefficients().size() );
        CHECK_THAT(  42., WithinRel( derivative.numerator().coefficients()[0] ) );
        CHECK_THAT(  38., WithinRel( derivative.numerator().coefficients()[1] ) );
        CHECK_THAT( -61., WithinRel( derivative.numerator().coefficients()[2] ) );
        CHECK_THAT(   0., WithinRel( derivative.numerator().coefficients()[3] ) );
        CHECK_THAT(   5., WithinRel( derivative.numerator().coefficients()[4] ) );
        CHECK( 5 == derivative.denominator().coefficients().size() );
        CHECK_THAT(  9., WithinRel( derivative.denominator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( derivative.denominator().coefficients()[1] ) );
        CHECK_THAT( 30., WithinRel( derivative.denominator().coefficients()[2] ) );
        CHECK_THAT(  0., WithinRel( derivative.denominator().coefficients()[3] ) );
        CHECK_THAT( 25., WithinRel( derivative.denominator().coefficients()[4] ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        PolynomialSeries< double > series( { 3., 0., 1. } );
        PolynomialSeriesRatio< double > other( { 3., 0., 1. }, { 5., 2. } );
        PolynomialSeriesRatio< double > result( { 0. }, { 0. } );

        result = -chunk;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT(   8., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(   7., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        chunk += 2;

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT(  -2., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT(  14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT(   3., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(   1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        chunk -= 2;

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        chunk += series;

        CHECK( 5 == chunk.numerator().coefficients().size() );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( 11., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( chunk.numerator().coefficients()[4] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        chunk -= series;

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        chunk *= 2;

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT( -16., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT(  28., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( -14., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(   2., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        chunk /= 2;

        CHECK( 4 == chunk.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( chunk.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( chunk.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( chunk.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( chunk.numerator().coefficients()[3] ) );
        CHECK( 3 == chunk.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( chunk.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.denominator().coefficients()[2] ) );

        result = chunk + 2;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT(  -2., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(   3., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = 2 + chunk;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT(  -2., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(   3., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk - 2;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -17., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = 2 - chunk;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT(  14., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk * 2;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -16., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  28., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   2., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = 2 * chunk;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -16., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  28., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   2., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk / 2;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -4. , WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  7. , WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -3.5, WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  0.5, WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = 2 / chunk;

        CHECK( 3 == result.numerator().coefficients().size() );
        CHECK_THAT(  6., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( 10., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk + series;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( 11., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = series + chunk;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( 11., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk - series;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -17., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -25., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -5., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = series - chunk;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( -14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  25., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(   5., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk * series;

        CHECK( 6 == result.numerator().coefficients().size() );
        CHECK_THAT( -24., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  42., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -29., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[5] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = series * chunk;

        CHECK( 6 == result.numerator().coefficients().size() );
        CHECK_THAT( -24., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  42., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -29., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[5] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk;
        result *= series;

        CHECK( 6 == result.numerator().coefficients().size() );
        CHECK_THAT( -24., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  42., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -29., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[5] ) );
        CHECK( 3 == result.denominator().coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT( 0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 5., WithinRel( result.denominator().coefficients()[2] ) );

        result = chunk / series;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 5 == result.denominator().coefficients().size() );
        CHECK_THAT(  9., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 18., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.denominator().coefficients()[4] ) );

        result = chunk;
        result /= series;

        CHECK( 4 == result.numerator().coefficients().size() );
        CHECK_THAT( -8., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT( 14., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -7., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  1., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK( 5 == result.denominator().coefficients().size() );
        CHECK_THAT(  9., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 18., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.denominator().coefficients()[4] ) );

        result = chunk;
        result *= other;

        CHECK( 6 == result.numerator().coefficients().size() );
        CHECK_THAT( -24., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  42., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -29., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[5] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk;
        result /= other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -40., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(   2., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 5 == result.denominator().coefficients().size() );
        CHECK_THAT(  9., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 18., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.denominator().coefficients()[4] ) );

        result = chunk * other;

        CHECK( 6 == result.numerator().coefficients().size() );
        CHECK_THAT( -24., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  42., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -29., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  17., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK_THAT(   1., WithinRel( result.numerator().coefficients()[5] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk / other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -40., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  -7., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(   2., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 5 == result.denominator().coefficients().size() );
        CHECK_THAT(  9., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 18., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT(  0., WithinRel( result.denominator().coefficients()[3] ) );
        CHECK_THAT(  5., WithinRel( result.denominator().coefficients()[4] ) );

        result = chunk;
        result += other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -31., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  11., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(   7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk;
        result -= other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -49., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -25., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -3., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk + other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -31., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT(  11., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(   7., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );

        result = chunk - other;

        CHECK( 5 == result.numerator().coefficients().size() );
        CHECK_THAT( -49., WithinRel( result.numerator().coefficients()[0] ) );
        CHECK_THAT(  54., WithinRel( result.numerator().coefficients()[1] ) );
        CHECK_THAT( -25., WithinRel( result.numerator().coefficients()[2] ) );
        CHECK_THAT(  -9., WithinRel( result.numerator().coefficients()[3] ) );
        CHECK_THAT(  -3., WithinRel( result.numerator().coefficients()[4] ) );
        CHECK( 4 == result.denominator().coefficients().size() );
        CHECK_THAT( 15., WithinRel( result.denominator().coefficients()[0] ) );
        CHECK_THAT(  6., WithinRel( result.denominator().coefficients()[1] ) );
        CHECK_THAT( 25., WithinRel( result.denominator().coefficients()[2] ) );
        CHECK_THAT( 10., WithinRel( result.denominator().coefficients()[3] ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of PolynomialSeries are given" ) {

      PolynomialSeriesRatio< double > left( { 1., 2., 3. }, { 3., 0., 4. } );
      PolynomialSeriesRatio< double > equal( { 1., 2., 3. }, { 3., 0., 4. } );
      PolynomialSeriesRatio< double > different( { 1., 0., 3. }, { 3., 0., 4. } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

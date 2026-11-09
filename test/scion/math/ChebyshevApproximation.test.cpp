// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "scion/math/ChebyshevApproximation.hpp"

// other includes

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X > using ChebyshevApproximation = math::ChebyshevApproximation< X, Y >;

SCENARIO( "ChebyshevApproximation" ) {

  GIVEN( "a function" ) {

    WHEN( "approximated on [-1,1]" ) {

      auto function = [] ( double x ) { return x; };
      ChebyshevApproximation< double > chunk( -1., 1., function, 10 );

      THEN( "a ChebyshevApproximation can be constructed and members can be tested" ) {

        CHECK( 10 == chunk.order() );

        CHECK( 11 == chunk.coefficients().size() );

        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );

        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );
      } // THEN

      THEN( "a ChebyshevApproximation can be evaluated" ) {

        CHECK_THAT( -1.0      , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( -0.9999999, WithinRel( chunk( -0.9999999 ) ) );
        CHECK_THAT( -0.999999 , WithinRel( chunk( -0.999999 ) ) );
        CHECK_THAT( -0.99999  , WithinRel( chunk( -0.99999 ) ) );
        CHECK_THAT( -0.9999   , WithinRel( chunk( -0.9999 ) ) );
        CHECK_THAT( -0.999    , WithinRel( chunk( -0.999 ) ) );
        CHECK_THAT( -0.99     , WithinRel( chunk( -0.99 ) ) );
        CHECK_THAT( -0.9      , WithinRel( chunk( -0.9 ) ) );
        CHECK_THAT( -0.5      , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( -0.05     , WithinRel( chunk( -0.05 ), 1e-12 ) );
        CHECK_THAT( -0.005    , WithinRel( chunk( -0.005 ), 1e-12 ) );
        CHECK_THAT( -0.0005   , WithinRel( chunk( -0.0005 ), 1e-11 ) );
        CHECK_THAT( -0.00005  , WithinRel( chunk( -0.00005 ), 1e-10 ) );
        CHECK_THAT( -0.000005 , WithinRel( chunk( -0.000005 ), 1e-9 ) );
        CHECK_THAT( -0.0000005, WithinRel( chunk( -0.0000005 ), 1e-8 ) );
        CHECK_THAT(  0.0      , WithinAbs( chunk(  0. ), 1e-12 ) );
        CHECK_THAT( +0.0000005, WithinRel( chunk(  0.0000005 ), 1e-8 ) );
        CHECK_THAT( +0.000005 , WithinRel( chunk(  0.000005 ), 1e-9 ) );
        CHECK_THAT( +0.00005  , WithinRel( chunk(  0.00005 ), 1e-10 ) );
        CHECK_THAT( +0.0005   , WithinRel( chunk(  0.0005 ), 1e-11 ) );
        CHECK_THAT( +0.005    , WithinRel( chunk(  0.005 ), 1e-12 ) );
        CHECK_THAT( +0.05     , WithinRel( chunk(  0.05 ), 1e-12 ) );
        CHECK_THAT( +0.5      , WithinRel( chunk(  0.5 ) ) );
        CHECK_THAT( +0.9      , WithinRel( chunk(  0.9 ) ) );
        CHECK_THAT( +0.99     , WithinRel( chunk(  0.99 ) ) );
        CHECK_THAT( +0.999    , WithinRel( chunk(  0.999 ) ) );
        CHECK_THAT( +0.9999   , WithinRel( chunk(  0.9999 ) ) );
        CHECK_THAT( +0.99999  , WithinRel( chunk(  0.99999 ) ) );
        CHECK_THAT( +0.999999 , WithinRel( chunk(  0.999999 ) ) );
        CHECK_THAT( +0.9999999, WithinRel( chunk(  0.9999999 ) ) );
        CHECK_THAT( +1.0      , WithinRel( chunk(  1. ) ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( -1. ) );
        CHECK( true == chunk.isInside(  0. ) );
        CHECK( true == chunk.isInside(  1. ) );

        CHECK( false == chunk.isContained( -1. ) );
        CHECK( true == chunk.isContained( 0. ) );
        CHECK( false == chunk.isContained( 1. ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        ChebyshevApproximation< double > small( -1., 1.,
                                                std::vector< double >{ 3., 0., 1. } );
        ChebyshevApproximation< double > result( -1., 1., std::vector< double >{ 0. } );

        result = -chunk;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[0], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        chunk += 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 2., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        chunk -= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        chunk += small;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[2] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        chunk -= small;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        chunk *= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 2., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        chunk /= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( chunk.upperLimit() ) );

        result = chunk + 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 2., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = 2. + chunk;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 2., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = chunk - 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( -2., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = 2. - chunk;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT(  2., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( -1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = chunk + small;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 3., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT( 1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 1., WithinRel( result.coefficients()[2] ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = chunk - small;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( -3., WithinRel( result.coefficients()[0] ) );
        CHECK_THAT(  1., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( -1., WithinRel( result.coefficients()[2] ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT(  0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = chunk * 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 2., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = 2. * chunk;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 2., WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );

        result = chunk / 2.;

        CHECK( 10 == result.order() );
        CHECK( 11 == result.coefficients().size() );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[0], 1e-12 ) );
        CHECK_THAT( 0.5, WithinRel( result.coefficients()[1] ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0.0, WithinAbs( result.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -1., WithinRel( result.lowerLimit() ) );
        CHECK_THAT(  1., WithinRel( result.upperLimit() ) );
      } // THEN
    } // WHEN

    WHEN( "approximated on [a,b]" ) {

      auto function = [] ( double x ) { return x; };
      ChebyshevApproximation< double > chunk( -2., 4., function, 10 );

      THEN( "a ChebyshevApproximation can be constructed and members can be tested" ) {

        CHECK( 10 == chunk.order() );

        CHECK( 11 == chunk.coefficients().size() );

        CHECK_THAT( 1., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );

        CHECK_THAT( -2., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  4., WithinRel( chunk.upperLimit() ) );
      } // THEN

      THEN( "a ChebyshevApproximation can be evaluated" ) {

        CHECK_THAT( -1.0      , WithinRel( chunk( -1. ) ) );
        CHECK_THAT( -0.9999999, WithinRel( chunk( -0.9999999 ) ) );
        CHECK_THAT( -0.999999 , WithinRel( chunk( -0.999999 ) ) );
        CHECK_THAT( -0.99999  , WithinRel( chunk( -0.99999 ) ) );
        CHECK_THAT( -0.9999   , WithinRel( chunk( -0.9999 ) ) );
        CHECK_THAT( -0.999    , WithinRel( chunk( -0.999 ) ) );
        CHECK_THAT( -0.99     , WithinRel( chunk( -0.99 ) ) );
        CHECK_THAT( -0.9      , WithinRel( chunk( -0.9 ) ) );
        CHECK_THAT( -0.5      , WithinRel( chunk( -0.5 ) ) );
        CHECK_THAT( -0.05     , WithinRel( chunk( -0.05 ), 1e-12 ) );
        CHECK_THAT( -0.005    , WithinRel( chunk( -0.005 ), 1e-12 ) );
        CHECK_THAT( -0.0005   , WithinRel( chunk( -0.0005 ), 1e-11 ) );
        CHECK_THAT( -0.00005  , WithinRel( chunk( -0.00005 ), 1e-10 ) );
        CHECK_THAT( -0.000005 , WithinRel( chunk( -0.000005 ), 1e-9 ) );
        CHECK_THAT( -0.0000005, WithinRel( chunk( -0.0000005 ), 1e-8 ) );
        CHECK_THAT(  0.0      , WithinAbs( chunk(  0. ), 1e-12 ) );
        CHECK_THAT( +0.0000005, WithinRel( chunk(  0.0000005 ), 1e-8 ) );
        CHECK_THAT( +0.000005 , WithinRel( chunk(  0.000005 ), 1e-9 ) );
        CHECK_THAT( +0.00005  , WithinRel( chunk(  0.00005 ), 1e-10 ) );
        CHECK_THAT( +0.0005   , WithinRel( chunk(  0.0005 ), 1e-11 ) );
        CHECK_THAT( +0.005    , WithinRel( chunk(  0.005 ), 1e-12 ) );
        CHECK_THAT( +0.05     , WithinRel( chunk(  0.05 ), 1e-12 ) );
        CHECK_THAT( +0.5      , WithinRel( chunk(  0.5 ) ) );
        CHECK_THAT( +0.9      , WithinRel( chunk(  0.9 ) ) );
        CHECK_THAT( +0.99     , WithinRel( chunk(  0.99 ) ) );
        CHECK_THAT( +0.999    , WithinRel( chunk(  0.999 ) ) );
        CHECK_THAT( +0.9999   , WithinRel( chunk(  0.9999 ) ) );
        CHECK_THAT( +0.99999  , WithinRel( chunk(  0.99999 ) ) );
        CHECK_THAT( +0.999999 , WithinRel( chunk(  0.999999 ) ) );
        CHECK_THAT( +0.9999999, WithinRel( chunk(  0.9999999 ) ) );
        CHECK_THAT( +1.0      , WithinRel( chunk(  1. ) ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( -2. ) );
        CHECK( true == chunk.isInside(  1. ) );
        CHECK( true == chunk.isInside(  4. ) );

        CHECK( false == chunk.isContained( -2. ) );
        CHECK( true == chunk.isContained( 1. ) );
        CHECK( false == chunk.isContained( 4. ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        chunk += 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -2., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  4., WithinRel( chunk.upperLimit() ) );

        chunk -= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -2., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  4., WithinRel( chunk.upperLimit() ) );

        chunk *= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 2., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -2., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  4., WithinRel( chunk.upperLimit() ) );

        chunk /= 2.;

        CHECK( 10 == chunk.order() );
        CHECK( 11 == chunk.coefficients().size() );
        CHECK_THAT( 1., WithinRel( chunk.coefficients()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.coefficients()[1] ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[2], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[3], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[4], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[5], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[6], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[7], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[8], 1e-12 ) );
        CHECK_THAT( 0., WithinAbs( chunk.coefficients()[9], 1e-12 ) );
        CHECK_THAT( -2., WithinRel( chunk.lowerLimit() ) );
        CHECK_THAT(  4., WithinRel( chunk.upperLimit() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of ChebyshevApproximation are given" ) {

      ChebyshevApproximation< double > left( -1., 1., std::vector< double >{ 1., 2., 3. } );
      ChebyshevApproximation< double > equal( -1., 1., std::vector< double >{ 1., 2., 3. } );
      ChebyshevApproximation< double > different( -1., 1., std::vector< double >{ 1., 0., 3. } );
      ChebyshevApproximation< double > otherdomain( 0., 1., std::vector< double >{ 1., 2., 3. } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different ) );
        CHECK( false == ( left == otherdomain ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different ) );
        CHECK( true == ( left != otherdomain ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "the domain is not valid" ) {

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ChebyshevApproximation< double >( 1., 1., std::vector< double >{ 1., 2. } ) );
        CHECK_THROWS( ChebyshevApproximation< double >( 1., -1., std::vector< double >{ 1., 2. } ) );
        CHECK_THROWS( ChebyshevApproximation< double >( -1., std::numeric_limits< double >::infinity(), std::vector< double >{ 1., 2. } ) );
        CHECK_THROWS( ChebyshevApproximation< double >( -std::numeric_limits< double >::infinity(), 1., std::vector< double >{ 1., 2. } ) );
        CHECK_THROWS( ChebyshevApproximation< double >( -std::numeric_limits< double >::infinity(),
                                                        std::numeric_limits< double >::infinity(), std::vector< double >{ 1., 2. } ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

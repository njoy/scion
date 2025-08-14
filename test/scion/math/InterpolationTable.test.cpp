// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/InterpolationTable.hpp"

// other includes

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "InterpolationTable" ) {

  GIVEN( "linearised data without boundaries and no jumps" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          interpolant );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be copy and move constructed" ) {

        InterpolationTable< double > copy( chunk );
        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.x().size() );
        CHECK( 4 == copy.y().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( 1., WithinRel( copy.x()[0] ) );
        CHECK_THAT( 2., WithinRel( copy.x()[1] ) );
        CHECK_THAT( 3., WithinRel( copy.x()[2] ) );
        CHECK_THAT( 4., WithinRel( copy.x()[3] ) );
        CHECK_THAT( 4., WithinRel( copy.y()[0] ) );
        CHECK_THAT( 3., WithinRel( copy.y()[1] ) );
        CHECK_THAT( 2., WithinRel( copy.y()[2] ) );
        CHECK_THAT( 1., WithinRel( copy.y()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( copy.domain() ) );

        InterpolationTable< double > move( std::move( copy ) );
        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.x().size() );
        CHECK( 4 == move.y().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( 1., WithinRel( move.x()[0] ) );
        CHECK_THAT( 2., WithinRel( move.x()[1] ) );
        CHECK_THAT( 3., WithinRel( move.x()[2] ) );
        CHECK_THAT( 4., WithinRel( move.x()[3] ) );
        CHECK_THAT( 4., WithinRel( move.y()[0] ) );
        CHECK_THAT( 3., WithinRel( move.y()[1] ) );
        CHECK_THAT( 2., WithinRel( move.y()[2] ) );
        CHECK_THAT( 1., WithinRel( move.y()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( move.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be copy and move assigned" ) {

        InterpolationTable< double > copy( { 1., 4. }, { 0., 0. } );
        copy = chunk;

        CHECK( 4 == copy.numberPoints() );
        CHECK( 1 == copy.numberRegions() );
        CHECK( 4 == copy.x().size() );
        CHECK( 4 == copy.y().size() );
        CHECK( 1 == copy.boundaries().size() );
        CHECK( 1 == copy.interpolants().size() );
        CHECK_THAT( 1., WithinRel( copy.x()[0] ) );
        CHECK_THAT( 2., WithinRel( copy.x()[1] ) );
        CHECK_THAT( 3., WithinRel( copy.x()[2] ) );
        CHECK_THAT( 4., WithinRel( copy.x()[3] ) );
        CHECK_THAT( 4., WithinRel( copy.y()[0] ) );
        CHECK_THAT( 3., WithinRel( copy.y()[1] ) );
        CHECK_THAT( 2., WithinRel( copy.y()[2] ) );
        CHECK_THAT( 1., WithinRel( copy.y()[3] ) );
        CHECK( 3 == copy.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == copy.interpolants()[0] );
        CHECK( true == copy.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( copy.domain() ) );

        InterpolationTable< double > move( { 1., 4. }, { 0., 0. } );
        move = std::move( copy );

        CHECK( 4 == move.numberPoints() );
        CHECK( 1 == move.numberRegions() );
        CHECK( 4 == move.x().size() );
        CHECK( 4 == move.y().size() );
        CHECK( 1 == move.boundaries().size() );
        CHECK( 1 == move.interpolants().size() );
        CHECK_THAT( 1., WithinRel( move.x()[0] ) );
        CHECK_THAT( 2., WithinRel( move.x()[1] ) );
        CHECK_THAT( 3., WithinRel( move.x()[2] ) );
        CHECK_THAT( 4., WithinRel( move.x()[3] ) );
        CHECK_THAT( 4., WithinRel( move.y()[0] ) );
        CHECK_THAT( 3., WithinRel( move.y()[1] ) );
        CHECK_THAT( 2., WithinRel( move.y()[2] ) );
        CHECK_THAT( 1., WithinRel( move.y()[3] ) );
        CHECK( 3 == move.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == move.interpolants()[0] );
        CHECK( true == move.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( move.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // ( 4 + 1 ) * 3 / 2 = 7.5
        CHECK_THAT( 7.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of an InterpolationTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 6. , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.5, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 16 / 2 - 64 / 3 - 5 / 2 + 1 / 3
        //          = 75 / 2 -  63 / 3 = 37.5 - 21
        CHECK_THAT( 16.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );
        InterpolationTable< double > same( { 1., 4. }, { 0., 3. } );
        InterpolationTable< double > threshold( { 2., 4. }, { 0., 2. } );
        InterpolationTable< double > nonzerothreshold( { 2., 4. }, { 1., 3. } );
        InterpolationTable< double > small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = -chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  3., WithinRel( result.x()[2] ) );
        CHECK_THAT(  4., WithinRel( result.x()[3] ) );
        CHECK_THAT( -4., WithinRel( result.y()[0] ) );
        CHECK_THAT( -3., WithinRel( result.y()[1] ) );
        CHECK_THAT( -2., WithinRel( result.y()[2] ) );
        CHECK_THAT( -1., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 6., WithinRel( result.y()[0] ) );
        CHECK_THAT( 5., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 3., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. + chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 6., WithinRel( result.y()[0] ) );
        CHECK_THAT( 5., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 3., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  3., WithinRel( result.x()[2] ) );
        CHECK_THAT(  4., WithinRel( result.x()[3] ) );
        CHECK_THAT(  2., WithinRel( result.y()[0] ) );
        CHECK_THAT(  1., WithinRel( result.y()[1] ) );
        CHECK_THAT(  0., WithinRel( result.y()[2] ) );
        CHECK_THAT( -1., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. - chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  3., WithinRel( result.x()[2] ) );
        CHECK_THAT(  4., WithinRel( result.x()[3] ) );
        CHECK_THAT( -2., WithinRel( result.y()[0] ) );
        CHECK_THAT( -1., WithinRel( result.y()[1] ) );
        CHECK_THAT(  0., WithinRel( result.y()[2] ) );
        CHECK_THAT(  1., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 2., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. * chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 2., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= same;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - same;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT(  4., WithinRel( result.y()[0] ) );
        CHECK_THAT(  2., WithinRel( result.y()[1] ) );
        CHECK_THAT(  0., WithinRel( result.y()[2] ) );
        CHECK_THAT( -2., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= threshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 3.0, WithinRel( result.y()[1] ) );
        CHECK_THAT( 3.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 3.0, WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - threshold;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT(  4., WithinRel( result.y()[0] ) );
        CHECK_THAT(  3., WithinRel( result.y()[1] ) );
        CHECK_THAT(  1., WithinRel( result.y()[2] ) );
        CHECK_THAT( -1., WithinRel( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += nonzerothreshold;

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= nonzerothreshold;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4.0, WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3.0, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2.0, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1.0, WithinRel( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 3., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 4., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - nonzerothreshold;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  2., WithinRel( result.x()[2] ) );
        CHECK_THAT(  3., WithinRel( result.x()[3] ) );
        CHECK_THAT(  4., WithinRel( result.x()[4] ) );
        CHECK_THAT(  4., WithinRel( result.y()[0] ) );
        CHECK_THAT(  3., WithinRel( result.y()[1] ) );
        CHECK_THAT(  2., WithinRel( result.y()[2] ) );
        CHECK_THAT(  0., WithinRel( result.y()[3] ) );
        CHECK_THAT( -2., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[1] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.y()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.y()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 5 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[4] ) );
        CHECK_THAT( 4.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 2.0, WithinRel( result.y()[1] ) );
        CHECK_THAT( 0.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 2.0, WithinRel( result.y()[3] ) );
        CHECK_THAT( 1.0, WithinRel( result.y()[4] ) );
        CHECK( 2 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be linearised" ) {

        InterpolationTable< double > linear = chunk.linearise();

        CHECK( 4 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 4 == linear.x().size() );
        CHECK( 4 == linear.y().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 3 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[3] ) );

        CHECK_THAT( 4., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 1., WithinRel( linear.y()[3] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "linearised data without boundaries and a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 4., 3., 2. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          interpolant );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        // the constructor will detect the jump and add interpolation regions
        // as required
        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3.5, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.5, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // ( 4 + 3 ) / 2 + ( 4 + 2 ) * 2 / 2 = 9.5
        CHECK_THAT( 9.5, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of an InterpolationTable can be calculated" ) {

        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0. , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5, WithinRel( cumulative[2] ) );
        CHECK_THAT( 7. , WithinRel( cumulative[3] ) );
        CHECK_THAT( 9.5, WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // region 1
        // f(x) = 5 - x
        // x f(x) = 5 x - x^2
        // primitive = 5 x^2 / 2 - x^3 / 3
        // integral = 5 * 4 / 2 - 8 / 3 - 5 / 2 + 1 / 3
        //          = 7.5 - 7 / 3
        // region 2
        // f(x) = 6 - x
        // x f(x) = 6 x - x^2
        // primitive = 3 x^2 - x^3 / 3
        // integral = 48 - 64 / 3 - 12 + 2 / 3
        //          = 36 - 62 / 3
        // sum = 43.5 - 69 / 3 = 22.5
        CHECK_THAT( 22.5, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "an InterpolationTable can be linearised" ) {

        InterpolationTable< double > linear = chunk.linearise();

        CHECK( 5 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 5 == linear.x().size() );
        CHECK( 5 == linear.y().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK( 1 == linear.boundaries()[0] );
        CHECK( 4 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1., WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2., WithinRel( linear.x()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.x()[3] ) );
        CHECK_THAT( 4., WithinRel( linear.x()[4] ) );

        CHECK_THAT( 4., WithinRel( linear.y()[0] ) );
        CHECK_THAT( 3., WithinRel( linear.y()[1] ) );
        CHECK_THAT( 4., WithinRel( linear.y()[2] ) );
        CHECK_THAT( 3., WithinRel( linear.y()[3] ) );
        CHECK_THAT( 2., WithinRel( linear.y()[4] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );
        InterpolationTable< double > same( { 1., 4. }, { 0., 3. } );
        InterpolationTable< double > threshold( { 2., 4. }, { 0., 2. } );
        InterpolationTable< double > nonzerothreshold( { 3., 4. }, { 1., 2. } );
        InterpolationTable< double > small( { 1., 3. }, { 0., 2. } );

        chunk += 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = -chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  2., WithinRel( result.x()[2] ) );
        CHECK_THAT(  3., WithinRel( result.x()[3] ) );
        CHECK_THAT(  4., WithinRel( result.x()[4] ) );
        CHECK_THAT( -4., WithinRel( result.y()[0] ) );
        CHECK_THAT( -3., WithinRel( result.y()[1] ) );
        CHECK_THAT( -4., WithinRel( result.y()[2] ) );
        CHECK_THAT( -3., WithinRel( result.y()[3] ) );
        CHECK_THAT( -2., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk + 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 6., WithinRel( result.y()[0] ) );
        CHECK_THAT( 5., WithinRel( result.y()[1] ) );
        CHECK_THAT( 6., WithinRel( result.y()[2] ) );
        CHECK_THAT( 5., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. + chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 6., WithinRel( result.y()[0] ) );
        CHECK_THAT( 5., WithinRel( result.y()[1] ) );
        CHECK_THAT( 6., WithinRel( result.y()[2] ) );
        CHECK_THAT( 5., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 2., WithinRel( result.y()[0] ) );
        CHECK_THAT( 1., WithinRel( result.y()[1] ) );
        CHECK_THAT( 2., WithinRel( result.y()[2] ) );
        CHECK_THAT( 1., WithinRel( result.y()[3] ) );
        CHECK_THAT( 0., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. - chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  2., WithinRel( result.x()[2] ) );
        CHECK_THAT(  3., WithinRel( result.x()[3] ) );
        CHECK_THAT(  4., WithinRel( result.x()[4] ) );
        CHECK_THAT( -2., WithinRel( result.y()[0] ) );
        CHECK_THAT( -1., WithinRel( result.y()[1] ) );
        CHECK_THAT( -2., WithinRel( result.y()[2] ) );
        CHECK_THAT( -1., WithinRel( result.y()[3] ) );
        CHECK_THAT(  0., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 8., WithinRel( result.y()[2] ) );
        CHECK_THAT( 6., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. * chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 8., WithinRel( result.y()[2] ) );
        CHECK_THAT( 6., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[4] ) );
        CHECK_THAT( 2. , WithinRel( result.y()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.y()[2] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[3] ) );
        CHECK_THAT( 1. , WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += same;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= same;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + same;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 4., WithinRel( result.y()[1] ) );
        CHECK_THAT( 5., WithinRel( result.y()[2] ) );
        CHECK_THAT( 5., WithinRel( result.y()[3] ) );
        CHECK_THAT( 5., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - same;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT(  4., WithinRel( result.y()[0] ) );
        CHECK_THAT(  2., WithinRel( result.y()[1] ) );
        CHECK_THAT(  3., WithinRel( result.y()[2] ) );
        CHECK_THAT(  1., WithinRel( result.y()[3] ) );
        CHECK_THAT( -1., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += threshold;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= threshold;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + threshold;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 3., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 4., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - threshold;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 3., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 2., WithinRel( result.y()[3] ) );
        CHECK_THAT( 0., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        chunk += nonzerothreshold;

        CHECK( 6 == chunk.x().size() );
        CHECK( 6 == chunk.y().size() );
        CHECK( 3 == chunk.boundaries().size() );
        CHECK( 3 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[5] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[5] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( 5 == chunk.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[2] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= nonzerothreshold;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + nonzerothreshold;

        CHECK( 6 == result.x().size() );
        CHECK( 6 == result.y().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 3., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.x()[5] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 3., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 3., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK_THAT( 4., WithinRel( result.y()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - nonzerothreshold;

        CHECK( 6 == result.x().size() );
        CHECK( 6 == result.y().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 3., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.x()[5] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 3., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 3., WithinRel( result.y()[3] ) );
        CHECK_THAT( 2., WithinRel( result.y()[4] ) );
        CHECK_THAT( 0., WithinRel( result.y()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        // this will add a second point at the lower end point
        result = chunk + small;

        CHECK( 6 == result.x().size() );
        CHECK( 6 == result.y().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 3., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.x()[5] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 4., WithinRel( result.y()[1] ) );
        CHECK_THAT( 5., WithinRel( result.y()[2] ) );
        CHECK_THAT( 5., WithinRel( result.y()[3] ) );
        CHECK_THAT( 3., WithinRel( result.y()[4] ) );
        CHECK_THAT( 2., WithinRel( result.y()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        // this will add a second point at the lower end point
        result = chunk - small;

        CHECK( 6 == result.x().size() );
        CHECK( 6 == result.y().size() );
        CHECK( 3 == result.boundaries().size() );
        CHECK( 3 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 3., WithinRel( result.x()[4] ) );
        CHECK_THAT( 4., WithinRel( result.x()[5] ) );
        CHECK_THAT( 4., WithinRel( result.y()[0] ) );
        CHECK_THAT( 2., WithinRel( result.y()[1] ) );
        CHECK_THAT( 3., WithinRel( result.y()[2] ) );
        CHECK_THAT( 1., WithinRel( result.y()[3] ) );
        CHECK_THAT( 3., WithinRel( result.y()[4] ) );
        CHECK_THAT( 2., WithinRel( result.y()[5] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( 5 == result.boundaries()[2] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[2] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions without a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };
      const std::vector< std::size_t > boundaries = { 1, 3 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK_THAT( 2.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 7.44236295915864, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 5.96630346237643, WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.44236295915864, WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 16.332650114006, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "an InterpolationTable can be linearised" ) {

        InterpolationTable< double > linear = chunk.linearise();

        CHECK( 18 == linear.numberPoints() );
        CHECK( 1 == linear.numberRegions() );

        CHECK( 18 == linear.x().size() );
        CHECK( 18 == linear.y().size() );
        CHECK( 1 == linear.boundaries().size() );
        CHECK( 1 == linear.interpolants().size() );

        CHECK( 17 == linear.boundaries()[0] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );

        CHECK_THAT( 1.   , WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2.125, WithinRel( linear.x()[2] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.x()[3] ) );
        CHECK_THAT( 2.375, WithinRel( linear.x()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.x()[5] ) );
        CHECK_THAT( 2.625, WithinRel( linear.x()[6] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.x()[7] ) );
        CHECK_THAT( 2.875, WithinRel( linear.x()[8] ) );
        CHECK_THAT( 3.   , WithinRel( linear.x()[9] ) );
        CHECK_THAT( 3.125, WithinRel( linear.x()[10] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.x()[11] ) );
        CHECK_THAT( 3.375, WithinRel( linear.x()[12] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.x()[13] ) );
        CHECK_THAT( 3.625, WithinRel( linear.x()[14] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.x()[15] ) );
        CHECK_THAT( 3.875, WithinRel( linear.x()[16] ) );
        CHECK_THAT( 4.   , WithinRel( linear.x()[17] ) );

        CHECK_THAT( 4.              , WithinRel( linear.y()[0] ) );
        CHECK_THAT( 3.              , WithinRel( linear.y()[1] ) );
        CHECK_THAT( 2.85048128530886, WithinRel( linear.y()[2] ) );
        CHECK_THAT( 2.70951129135145, WithinRel( linear.y()[3] ) );
        CHECK_THAT( 2.57616511633150, WithinRel( linear.y()[4] ) );
        CHECK_THAT( 2.44966028678679, WithinRel( linear.y()[5] ) );
        CHECK_THAT( 2.32932893596581, WithinRel( linear.y()[6] ) );
        CHECK_THAT( 2.21459646033567, WithinRel( linear.y()[7] ) );
        CHECK_THAT( 2.10496492439848, WithinRel( linear.y()[8] ) );
        CHECK_THAT( 2.              , WithinRel( linear.y()[9] ) );
        CHECK_THAT( 1.85810031827028, WithinRel( linear.y()[10] ) );
        CHECK_THAT( 1.72176678584324, WithinRel( linear.y()[11] ) );
        CHECK_THAT( 1.59057916034679, WithinRel( linear.y()[12] ) );
        CHECK_THAT( 1.46416306545103, WithinRel( linear.y()[13] ) );
        CHECK_THAT( 1.34218354996644, WithinRel( linear.y()[14] ) );
        CHECK_THAT( 1.22433973930853, WithinRel( linear.y()[15] ) );
        CHECK_THAT( 1.11036036428687, WithinRel( linear.y()[16] ) );
        CHECK_THAT( 1.              , WithinRel( linear.y()[17] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = -chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT(  1., WithinRel( result.x()[0] ) );
        CHECK_THAT(  2., WithinRel( result.x()[1] ) );
        CHECK_THAT(  3., WithinRel( result.x()[2] ) );
        CHECK_THAT(  4., WithinRel( result.x()[3] ) );
        CHECK_THAT( -4., WithinRel( result.y()[0] ) );
        CHECK_THAT( -3., WithinRel( result.y()[1] ) );
        CHECK_THAT( -2., WithinRel( result.y()[2] ) );
        CHECK_THAT( -1., WithinRel( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 2., WithinRel( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. * chunk;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 3., WithinRel( result.x()[2] ) );
        CHECK_THAT( 4., WithinRel( result.x()[3] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 4., WithinRel( result.y()[2] ) );
        CHECK_THAT( 2., WithinRel( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1. , WithinRel( result.x()[0] ) );
        CHECK_THAT( 2. , WithinRel( result.x()[1] ) );
        CHECK_THAT( 3. , WithinRel( result.x()[2] ) );
        CHECK_THAT( 4. , WithinRel( result.x()[3] ) );
        CHECK_THAT( 2.0, WithinRel( result.y()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[1] ) );
        CHECK_THAT( 1.0, WithinRel( result.y()[2] ) );
        CHECK_THAT( 0.5, WithinRel( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );
        InterpolationTable< double > right( { 1., 4. }, { 0., 0. } );

        // scalar operations
        CHECK_THROWS( chunk += 2. );
        CHECK_THROWS( chunk -= 2. );
        CHECK_THROWS( result = chunk + 2. );
        CHECK_THROWS( result = chunk - 2. );
        CHECK_THROWS( result = 2. + chunk );
        CHECK_THROWS( result = 2. - chunk );

        // table operations
        CHECK_THROWS( chunk += right );
        CHECK_THROWS( chunk -= right );
        CHECK_THROWS( result = chunk + right );
        CHECK_THROWS( result = chunk - right );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 4., 3., 2. };
      const std::vector< std::size_t > boundaries = { 1, 4 };
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK_THAT( 3.5, WithinRel( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK_THAT( 3.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "an InterpolationTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 9.44236295915864, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral();
        CHECK( 5 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[1] ) );
        CHECK_THAT( 3.5             , WithinRel( cumulative[2] ) );
        CHECK_THAT( 6.96630346237643, WithinRel( cumulative[3] ) );
        CHECK_THAT( 9.44236295915864, WithinRel( cumulative[4] ) );
      } // THEN

      THEN( "the first raw moment of an InterpolationTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 22.332650114006, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "the domain can be tested" ) {

        CHECK( true == chunk.isInside( 1.0 ) );
        CHECK( true == chunk.isInside( 2.5 ) );
        CHECK( true == chunk.isInside( 4.0 ) );

        CHECK( false == chunk.isContained( 1.0 ) );
        CHECK( true == chunk.isContained( 2.5 ) );
        CHECK( false == chunk.isContained( 4.0 ) );

        CHECK( true == chunk.isSameDomain( IntervalDomain< double >( 1., 4. ) ) );
        CHECK( false == chunk.isSameDomain( IntervalDomain< double >( 0., 4. ) ) );
        CHECK( false == chunk.isSameDomain( OpenDomain< double >() ) );
      } // THEN

      THEN( "an InterpolationTable can be linearised" ) {

        InterpolationTable< double > linear = chunk.linearise();

        CHECK( 12 == linear.numberPoints() );
        CHECK( 2 == linear.numberRegions() );

        CHECK( 12 == linear.x().size() );
        CHECK( 12 == linear.y().size() );
        CHECK( 2 == linear.boundaries().size() );
        CHECK( 2 == linear.interpolants().size() );

        CHECK(  1 == linear.boundaries()[0] );
        CHECK( 11 == linear.boundaries()[1] );

        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[1] );

        CHECK_THAT( 1.   , WithinRel( linear.x()[0] ) );
        CHECK_THAT( 2.   , WithinRel( linear.x()[1] ) );
        CHECK_THAT( 2.   , WithinRel( linear.x()[2] ) );
        CHECK_THAT( 2.125, WithinRel( linear.x()[3] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.x()[4] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.x()[5] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.x()[6] ) );
        CHECK_THAT( 3.   , WithinRel( linear.x()[7] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.x()[8] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.x()[9] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.x()[10] ) );
        CHECK_THAT( 4.   , WithinRel( linear.x()[11] ) );

        CHECK_THAT( 4.              , WithinRel( linear.y()[0] ) );
        CHECK_THAT( 3.              , WithinRel( linear.y()[1] ) );
        CHECK_THAT( 4.              , WithinRel( linear.y()[2] ) );
        CHECK_THAT( 3.85048128530886, WithinRel( linear.y()[3] ) );
        CHECK_THAT( 3.70951129135145, WithinRel( linear.y()[4] ) );
        CHECK_THAT( 3.44966028678679, WithinRel( linear.y()[5] ) );
        CHECK_THAT( 3.21459646033567, WithinRel( linear.y()[6] ) );
        CHECK_THAT( 3.              , WithinRel( linear.y()[7] ) );
        CHECK_THAT( 2.72176678584324, WithinRel( linear.y()[8] ) );
        CHECK_THAT( 2.46416306545103, WithinRel( linear.y()[9] ) );
        CHECK_THAT( 2.22433973930853, WithinRel( linear.y()[10] ) );
        CHECK_THAT( 2.              , WithinRel( linear.y()[11] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "some arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );

        chunk *= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 8., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 6., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = -chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( -4., WithinRel( result.y()[0] ) );
        CHECK_THAT( -3., WithinRel( result.y()[1] ) );
        CHECK_THAT( -4., WithinRel( result.y()[2] ) );
        CHECK_THAT( -3., WithinRel( result.y()[3] ) );
        CHECK_THAT( -2., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 8., WithinRel( result.y()[2] ) );
        CHECK_THAT( 6., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = 2. * chunk;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 8., WithinRel( result.y()[0] ) );
        CHECK_THAT( 6., WithinRel( result.y()[1] ) );
        CHECK_THAT( 8., WithinRel( result.y()[2] ) );
        CHECK_THAT( 6., WithinRel( result.y()[3] ) );
        CHECK_THAT( 4., WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK_THAT( 1., WithinRel( result.x()[0] ) );
        CHECK_THAT( 2., WithinRel( result.x()[1] ) );
        CHECK_THAT( 2., WithinRel( result.x()[2] ) );
        CHECK_THAT( 3., WithinRel( result.x()[3] ) );
        CHECK_THAT( 4., WithinRel( result.x()[4] ) );
        CHECK_THAT( 2. , WithinRel( result.y()[0] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[1] ) );
        CHECK_THAT( 2. , WithinRel( result.y()[2] ) );
        CHECK_THAT( 1.5, WithinRel( result.y()[3] ) );
        CHECK_THAT( 1. , WithinRel( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( false == result.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN

      THEN( "some arithmetic operations cannot be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );
        InterpolationTable< double > right( { 1., 4. }, { 0., 0. } );

        // scalar operations
        CHECK_THROWS( chunk += 2. );
        CHECK_THROWS( chunk -= 2. );
        CHECK_THROWS( result = chunk + 2. );
        CHECK_THROWS( result = chunk - 2. );
        CHECK_THROWS( result = 2. + chunk );
        CHECK_THROWS( result = 2. - chunk );

        // table operations
        CHECK_THROWS( chunk += right );
        CHECK_THROWS( chunk -= right );
        CHECK_THROWS( result = chunk + right );
        CHECK_THROWS( result = chunk - right );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump and boundaries "
         "that point to the second x value in the jump" ) {

    // note: at construction time, the boundary value will be set to the first point in
    //       the jump. As a result, the final data contained in this InterpolationTable is the
    //       same as the previous test.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 4., 3., 2. };
      const std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end of the jump
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "a InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );           // <-- this is changed from 2 to 1
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the end that goes to zero" ) {

    // note: at construction time, the last x and y value will be removed and the last
    //       boundary value will be decremented by 1.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4., 4. }; // <-- jump at end
      const std::vector< double > y = { 4., 3., 2., 1., 0. }; // <-- last value is zero
      const std::vector< std::size_t > boundaries = { 1, 4 }; // <-- pointing to end
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) ); // <-- last point removed
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) ); // <-- last point removed
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "non-linearised data with multiple regions with a jump at the beginning from zero on" ) {

    // note: at construction time, the first x and y value will be removed and all
    //       boundary values will be decremented by 1.

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 1., 2., 3., 4. }; // <-- jump at beginning
      const std::vector< double > y = { 0., 4., 3., 2., 1. }; // <-- first value is zero
      const std::vector< std::size_t > boundaries = { 2, 4 }; // <-- pointing to end
      const std::vector< InterpolationType > interpolants = {

        InterpolationType::LinearLinear,
        InterpolationType::LinearLog
      };

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          std::move( boundaries ),
                                          std::move( interpolants ) );

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) ); // <-- first point removed
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) ); // <-- first point removed
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );         // <-- boundary value reset
        CHECK( 3 == chunk.boundaries()[1] );         // <-- boundary value reset
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "comparison operators" ) {

    WHEN( "two instances of InterpolationTable are given" ) {

      InterpolationTable< double > left( { 1., 2., 3. }, { 1., 2., 3. } );
      InterpolationTable< double > equal( { 1., 2., 3. }, { 1., 2., 3. } );
      InterpolationTable< double > different1( { 1., 2., 3. }, { 1., 0., 3. } );
      InterpolationTable< double > different2( { 1., 2., 3. }, { 1., 2., 3. }, InterpolationType::LogLog );
      InterpolationTable< double > different3( { 1., 2., 3. }, { 1., 2., 3. },
                                               { 1, 2 },
                                               { InterpolationType::LinearLinear, InterpolationType::LogLog } );

      THEN( "they can be compared" ) {

        CHECK( true == ( left == left ) );
        CHECK( true == ( left == equal ) );
        CHECK( false == ( left == different1 ) );
        CHECK( false == ( left == different2 ) );
        CHECK( false == ( left == different3 ) );

        CHECK( false == ( left != left ) );
        CHECK( false == ( left != equal ) );
        CHECK( true == ( left != different1 ) );
        CHECK( true == ( left != different2 ) );
        CHECK( true == ( left != different3 ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for an InterpolationTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( empty, empty ) );
        CHECK_THROWS( InterpolationTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the boundaries and interpolants do not have the same size" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };
      std::vector< std::size_t > boundaries = { 3 };
      std::vector< InterpolationType > interpolants = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid contains a triple x value" ) {

      std::vector< double > x = { 1., 2., 2., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 3., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the beginning" ) {

      std::vector< double > x = { 1., 1., 3., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a triplicate point at the beginning" ) {

      std::vector< double > x = { 1., 1., 1., 3., 4. };
      std::vector< double > y = { 0., 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a jump at the end" ) {

      std::vector< double > x = { 1., 2., 4., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the last boundary does not point to the last point" ) {

      std::vector< double > x = { 1., 2., 4., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };
      std::vector< std::size_t > boundaries = { 2 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ),
                                                    std::move( boundaries ),
                                                    std::move( interpolants ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

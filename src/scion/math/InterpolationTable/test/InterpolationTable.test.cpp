#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

// what we are testing
#include "scion/math/InterpolationTable.hpp"

// other includes

// convenience typedefs
using namespace Catch;
using namespace njoy::scion;
template < typename X, typename Y = X >
using InterpolationTable = math::InterpolationTable< X, Y >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "InterpolationTable" ) {

  GIVEN( "data without boundaries and no jumps" ) {

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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == chunk.isLinearised() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );
        CHECK( 2.5 == Approx( chunk( 2.5 ) ) );
        CHECK( 1.5 == Approx( chunk( 3.5 ) ) );
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

        chunk += 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 6. == Approx( chunk.y()[0] ) );
        CHECK( 5. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 8. == Approx( chunk.y()[0] ) );
        CHECK( 6. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 2. == Approx( chunk.y()[3] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 3 == chunk.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 1 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 1 == result.boundaries().size() );
        CHECK( 1 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 3. == Approx( result.x()[2] ) );
        CHECK( 4. == Approx( result.x()[3] ) );
        CHECK( 6. == Approx( result.y()[0] ) );
        CHECK( 5. == Approx( result.y()[1] ) );
        CHECK( 4. == Approx( result.y()[2] ) );
        CHECK( 3. == Approx( result.y()[3] ) );
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
        CHECK(  1. == Approx( result.x()[0] ) );
        CHECK(  2. == Approx( result.x()[1] ) );
        CHECK(  3. == Approx( result.x()[2] ) );
        CHECK(  4. == Approx( result.x()[3] ) );
        CHECK(  2. == Approx( result.y()[0] ) );
        CHECK(  1. == Approx( result.y()[1] ) );
        CHECK(  0. == Approx( result.y()[2] ) );
        CHECK( -1. == Approx( result.y()[3] ) );
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
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 3. == Approx( result.x()[2] ) );
        CHECK( 4. == Approx( result.x()[3] ) );
        CHECK( 8. == Approx( result.y()[0] ) );
        CHECK( 6. == Approx( result.y()[1] ) );
        CHECK( 4. == Approx( result.y()[2] ) );
        CHECK( 2. == Approx( result.y()[3] ) );
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
        CHECK( 1.  == Approx( result.x()[0] ) );
        CHECK( 2.  == Approx( result.x()[1] ) );
        CHECK( 3.  == Approx( result.x()[2] ) );
        CHECK( 4.  == Approx( result.x()[3] ) );
        CHECK( 2.0 == Approx( result.y()[0] ) );
        CHECK( 1.5 == Approx( result.y()[1] ) );
        CHECK( 1.0 == Approx( result.y()[2] ) );
        CHECK( 0.5 == Approx( result.y()[3] ) );
        CHECK( 3 == result.boundaries()[0] );
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

        CHECK( 1. == Approx( linear.x()[0] ) );
        CHECK( 2. == Approx( linear.x()[1] ) );
        CHECK( 3. == Approx( linear.x()[2] ) );
        CHECK( 4. == Approx( linear.x()[3] ) );

        CHECK( 4. == Approx( linear.y()[0] ) );
        CHECK( 3. == Approx( linear.y()[1] ) );
        CHECK( 2. == Approx( linear.y()[2] ) );
        CHECK( 1. == Approx( linear.y()[3] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data without boundaries and a jump" ) {

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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 4. == Approx( chunk( 2. ) ) );
        CHECK( 3. == Approx( chunk( 3. ) ) );
        CHECK( 2. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );
        CHECK( 3.5 == Approx( chunk( 2.5 ) ) );
        CHECK( 2.5 == Approx( chunk( 3.5 ) ) );
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

        CHECK( 1. == Approx( linear.x()[0] ) );
        CHECK( 2. == Approx( linear.x()[1] ) );
        CHECK( 2. == Approx( linear.x()[2] ) );
        CHECK( 3. == Approx( linear.x()[3] ) );
        CHECK( 4. == Approx( linear.x()[4] ) );

        CHECK( 4. == Approx( linear.y()[0] ) );
        CHECK( 3. == Approx( linear.y()[1] ) );
        CHECK( 4. == Approx( linear.y()[2] ) );
        CHECK( 3. == Approx( linear.y()[3] ) );
        CHECK( 2. == Approx( linear.y()[4] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );

        chunk += 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 6. == Approx( chunk.y()[0] ) );
        CHECK( 5. == Approx( chunk.y()[1] ) );
        CHECK( 6. == Approx( chunk.y()[2] ) );
        CHECK( 5. == Approx( chunk.y()[3] ) );
        CHECK( 4. == Approx( chunk.y()[4] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 8. == Approx( chunk.y()[0] ) );
        CHECK( 6. == Approx( chunk.y()[1] ) );
        CHECK( 8. == Approx( chunk.y()[2] ) );
        CHECK( 6. == Approx( chunk.y()[3] ) );
        CHECK( 4. == Approx( chunk.y()[4] ) );
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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 6. == Approx( result.y()[0] ) );
        CHECK( 5. == Approx( result.y()[1] ) );
        CHECK( 6. == Approx( result.y()[2] ) );
        CHECK( 5. == Approx( result.y()[3] ) );
        CHECK( 4. == Approx( result.y()[4] ) );
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
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 2. == Approx( result.y()[0] ) );
        CHECK( 1. == Approx( result.y()[1] ) );
        CHECK( 2. == Approx( result.y()[2] ) );
        CHECK( 1. == Approx( result.y()[3] ) );
        CHECK( 0. == Approx( result.y()[4] ) );
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
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 8. == Approx( result.y()[0] ) );
        CHECK( 6. == Approx( result.y()[1] ) );
        CHECK( 8. == Approx( result.y()[2] ) );
        CHECK( 6. == Approx( result.y()[3] ) );
        CHECK( 4. == Approx( result.y()[4] ) );
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
        CHECK( 1.  == Approx( result.x()[0] ) );
        CHECK( 2.  == Approx( result.x()[1] ) );
        CHECK( 2.  == Approx( result.x()[2] ) );
        CHECK( 3.  == Approx( result.x()[3] ) );
        CHECK( 4.  == Approx( result.x()[4] ) );
        CHECK( 2.  == Approx( result.y()[0] ) );
        CHECK( 1.5 == Approx( result.y()[1] ) );
        CHECK( 2.  == Approx( result.y()[2] ) );
        CHECK( 1.5 == Approx( result.y()[3] ) );
        CHECK( 1.  == Approx( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with multiple regions without a jump" ) {

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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "an InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 3. == Approx( chunk( 2. ) ) );
        CHECK( 2. == Approx( chunk( 3. ) ) );
        CHECK( 1. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK( 2.449660287 == Approx( chunk( 2.5 ) ) );
        CHECK( 1.464163065 == Approx( chunk( 3.5 ) ) );
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

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 2.    == Approx( linear.x()[1] ) );
        CHECK( 2.125 == Approx( linear.x()[2] ) );
        CHECK( 2.25  == Approx( linear.x()[3] ) );
        CHECK( 2.375 == Approx( linear.x()[4] ) );
        CHECK( 2.5   == Approx( linear.x()[5] ) );
        CHECK( 2.625 == Approx( linear.x()[6] ) );
        CHECK( 2.75  == Approx( linear.x()[7] ) );
        CHECK( 2.875 == Approx( linear.x()[8] ) );
        CHECK( 3.    == Approx( linear.x()[9] ) );
        CHECK( 3.125 == Approx( linear.x()[10] ) );
        CHECK( 3.25  == Approx( linear.x()[11] ) );
        CHECK( 3.375 == Approx( linear.x()[12] ) );
        CHECK( 3.5   == Approx( linear.x()[13] ) );
        CHECK( 3.625 == Approx( linear.x()[14] ) );
        CHECK( 3.75  == Approx( linear.x()[15] ) );
        CHECK( 3.875 == Approx( linear.x()[16] ) );
        CHECK( 4.    == Approx( linear.x()[17] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.          == Approx( linear.y()[1] ) );
        CHECK( 2.850481285 == Approx( linear.y()[2] ) );
        CHECK( 2.709511291 == Approx( linear.y()[3] ) );
        CHECK( 2.576165116 == Approx( linear.y()[4] ) );
        CHECK( 2.449660287 == Approx( linear.y()[5] ) );
        CHECK( 2.329328936 == Approx( linear.y()[6] ) );
        CHECK( 2.21459646  == Approx( linear.y()[7] ) );
        CHECK( 2.104964924 == Approx( linear.y()[8] ) );
        CHECK( 2.          == Approx( linear.y()[9] ) );
        CHECK( 1.858100318 == Approx( linear.y()[10] ) );
        CHECK( 1.721766786 == Approx( linear.y()[11] ) );
        CHECK( 1.59057916  == Approx( linear.y()[12] ) );
        CHECK( 1.464163065 == Approx( linear.y()[13] ) );
        CHECK( 1.34218355  == Approx( linear.y()[14] ) );
        CHECK( 1.224339739 == Approx( linear.y()[15] ) );
        CHECK( 1.110360364 == Approx( linear.y()[16] ) );
        CHECK( 1.          == Approx( linear.y()[17] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );

        chunk += 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 6. == Approx( chunk.y()[0] ) );
        CHECK( 5. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 8. == Approx( chunk.y()[0] ) );
        CHECK( 6. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 2. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 4 == chunk.numberPoints() );
        CHECK( 2 == chunk.numberRegions() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 3. == Approx( chunk.x()[2] ) );
        CHECK( 4. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 2. == Approx( chunk.y()[2] ) );
        CHECK( 1. == Approx( chunk.y()[3] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 3 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 3. == Approx( result.x()[2] ) );
        CHECK( 4. == Approx( result.x()[3] ) );
        CHECK( 6. == Approx( result.y()[0] ) );
        CHECK( 5. == Approx( result.y()[1] ) );
        CHECK( 4. == Approx( result.y()[2] ) );
        CHECK( 3. == Approx( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 4 == result.numberPoints() );
        CHECK( 2 == result.numberRegions() );
        CHECK( 4 == result.x().size() );
        CHECK( 4 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK(  1. == Approx( result.x()[0] ) );
        CHECK(  2. == Approx( result.x()[1] ) );
        CHECK(  3. == Approx( result.x()[2] ) );
        CHECK(  4. == Approx( result.x()[3] ) );
        CHECK(  2. == Approx( result.y()[0] ) );
        CHECK(  1. == Approx( result.y()[1] ) );
        CHECK(  0. == Approx( result.y()[2] ) );
        CHECK( -1. == Approx( result.y()[3] ) );
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
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 3. == Approx( result.x()[2] ) );
        CHECK( 4. == Approx( result.x()[3] ) );
        CHECK( 8. == Approx( result.y()[0] ) );
        CHECK( 6. == Approx( result.y()[1] ) );
        CHECK( 4. == Approx( result.y()[2] ) );
        CHECK( 2. == Approx( result.y()[3] ) );
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
        CHECK( 1.  == Approx( result.x()[0] ) );
        CHECK( 2.  == Approx( result.x()[1] ) );
        CHECK( 3.  == Approx( result.x()[2] ) );
        CHECK( 4.  == Approx( result.x()[3] ) );
        CHECK( 2.0 == Approx( result.y()[0] ) );
        CHECK( 1.5 == Approx( result.y()[1] ) );
        CHECK( 1.0 == Approx( result.y()[2] ) );
        CHECK( 0.5 == Approx( result.y()[3] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 3 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "data with multiple regions with a jump" ) {

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
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( false == chunk.isLinearised() );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a InterpolationTable can be evaluated" ) {

        // values of x in the x grid
        CHECK( 4. == Approx( chunk( 1. ) ) );
        CHECK( 4. == Approx( chunk( 2. ) ) );
        CHECK( 3. == Approx( chunk( 3. ) ) );
        CHECK( 2. == Approx( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK( 0. == Approx( chunk( 0. ) ) );
        CHECK( 0. == Approx( chunk( 5. ) ) );

        // values of x inside the x grid (lin-lin piece)
        CHECK( 3.5 == Approx( chunk( 1.5 ) ) );

        // values of x inside the x grid (lin-log piece)
        CHECK( 3.449660287 == Approx( chunk( 2.5 ) ) );
        CHECK( 2.464163065 == Approx( chunk( 3.5 ) ) );
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

        CHECK( 1.    == Approx( linear.x()[0] ) );
        CHECK( 2.    == Approx( linear.x()[1] ) );
        CHECK( 2.    == Approx( linear.x()[2] ) );
        CHECK( 2.125 == Approx( linear.x()[3] ) );
        CHECK( 2.25  == Approx( linear.x()[4] ) );
        CHECK( 2.5   == Approx( linear.x()[5] ) );
        CHECK( 2.75  == Approx( linear.x()[6] ) );
        CHECK( 3.    == Approx( linear.x()[7] ) );
        CHECK( 3.25  == Approx( linear.x()[8] ) );
        CHECK( 3.5   == Approx( linear.x()[9] ) );
        CHECK( 3.75  == Approx( linear.x()[10] ) );
        CHECK( 4.    == Approx( linear.x()[11] ) );

        CHECK( 4.          == Approx( linear.y()[0] ) );
        CHECK( 3.          == Approx( linear.y()[1] ) );
        CHECK( 4.          == Approx( linear.y()[2] ) );
        CHECK( 3.850481285 == Approx( linear.y()[3] ) );
        CHECK( 3.709511291 == Approx( linear.y()[4] ) );
        CHECK( 3.449660287 == Approx( linear.y()[5] ) );
        CHECK( 3.21459646  == Approx( linear.y()[6] ) );
        CHECK( 3.          == Approx( linear.y()[7] ) );
        CHECK( 2.721766786 == Approx( linear.y()[8] ) );
        CHECK( 2.464163065 == Approx( linear.y()[9] ) );
        CHECK( 2.224339739 == Approx( linear.y()[10] ) );
        CHECK( 2.          == Approx( linear.y()[11] ) );

        CHECK( true == linear.isLinearised() );
      } // THEN

      THEN( "arithmetic operations can be performed" ) {

        InterpolationTable< double > result( { 1., 4. }, { 0., 0. } );

        chunk += 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 6. == Approx( chunk.y()[0] ) );
        CHECK( 5. == Approx( chunk.y()[1] ) );
        CHECK( 6. == Approx( chunk.y()[2] ) );
        CHECK( 5. == Approx( chunk.y()[3] ) );
        CHECK( 4. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk -= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk *= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 8. == Approx( chunk.y()[0] ) );
        CHECK( 6. == Approx( chunk.y()[1] ) );
        CHECK( 8. == Approx( chunk.y()[2] ) );
        CHECK( 6. == Approx( chunk.y()[3] ) );
        CHECK( 4. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        chunk /= 2.;

        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 2 == chunk.boundaries().size() );
        CHECK( 2 == chunk.interpolants().size() );
        CHECK( 1. == Approx( chunk.x()[0] ) );
        CHECK( 2. == Approx( chunk.x()[1] ) );
        CHECK( 2. == Approx( chunk.x()[2] ) );
        CHECK( 3. == Approx( chunk.x()[3] ) );
        CHECK( 4. == Approx( chunk.x()[4] ) );
        CHECK( 4. == Approx( chunk.y()[0] ) );
        CHECK( 3. == Approx( chunk.y()[1] ) );
        CHECK( 4. == Approx( chunk.y()[2] ) );
        CHECK( 3. == Approx( chunk.y()[3] ) );
        CHECK( 2. == Approx( chunk.y()[4] ) );
        CHECK( 1 == chunk.boundaries()[0] );
        CHECK( 4 == chunk.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == chunk.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == chunk.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        result = chunk + 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 6. == Approx( result.y()[0] ) );
        CHECK( 5. == Approx( result.y()[1] ) );
        CHECK( 6. == Approx( result.y()[2] ) );
        CHECK( 5. == Approx( result.y()[3] ) );
        CHECK( 4. == Approx( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk - 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 2. == Approx( result.y()[0] ) );
        CHECK( 1. == Approx( result.y()[1] ) );
        CHECK( 2. == Approx( result.y()[2] ) );
        CHECK( 1. == Approx( result.y()[3] ) );
        CHECK( 0. == Approx( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk * 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1. == Approx( result.x()[0] ) );
        CHECK( 2. == Approx( result.x()[1] ) );
        CHECK( 2. == Approx( result.x()[2] ) );
        CHECK( 3. == Approx( result.x()[3] ) );
        CHECK( 4. == Approx( result.x()[4] ) );
        CHECK( 8. == Approx( result.y()[0] ) );
        CHECK( 6. == Approx( result.y()[1] ) );
        CHECK( 8. == Approx( result.y()[2] ) );
        CHECK( 6. == Approx( result.y()[3] ) );
        CHECK( 4. == Approx( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );

        result = chunk / 2.;

        CHECK( 5 == result.x().size() );
        CHECK( 5 == result.y().size() );
        CHECK( 2 == result.boundaries().size() );
        CHECK( 2 == result.interpolants().size() );
        CHECK( 1.  == Approx( result.x()[0] ) );
        CHECK( 2.  == Approx( result.x()[1] ) );
        CHECK( 2.  == Approx( result.x()[2] ) );
        CHECK( 3.  == Approx( result.x()[3] ) );
        CHECK( 4.  == Approx( result.x()[4] ) );
        CHECK( 2.  == Approx( result.y()[0] ) );
        CHECK( 1.5 == Approx( result.y()[1] ) );
        CHECK( 2.  == Approx( result.y()[2] ) );
        CHECK( 1.5 == Approx( result.y()[3] ) );
        CHECK( 1.  == Approx( result.y()[4] ) );
        CHECK( 1 == result.boundaries()[0] );
        CHECK( 4 == result.boundaries()[1] );
        CHECK( InterpolationType::LinearLinear == result.interpolants()[0] );
        CHECK( InterpolationType::LinearLog == result.interpolants()[1] );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( result.domain() ) );
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

    WHEN( "the x grid has a jump at the end" ) {

      std::vector< double > x = { 1., 2., 4., 4. };
      std::vector< double > y = { 4., 3., 1., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( InterpolationTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

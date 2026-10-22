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

SCENARIO( "InterpolationTable - coulomb penetrability specific tests" ) {

  GIVEN( "linearised data without a non-optional threshold" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 1., 2., 3., 4. };
      const std::vector< double > y = { 4., 3., 2., 1. };
      InterpolationType interpolant = InterpolationType::LinearLinear;

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          interpolant, false, 0. );

      THEN( "the threshold is set to None" ) {

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
        CHECK( std::nullopt == chunk.threshold() ); // <-- threshold is None
        CHECK( true == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "coulomb penetrability data" ) {

    WHEN( "the data is given explicitly" ) {

      const std::vector< double > x = { 100., 200., 300., 400., 500. };
      const std::vector< double > y = { 1.314e-60, 4.7703e-43, 2.6024e-35, 1.0178e-30, 1.3491e-27 };
      InterpolationType interpolant = InterpolationType::CoulombPenetrability;

      InterpolationTable< double > chunk( std::move( x ), std::move( y ),
                                          interpolant, false, 0. );

      // Unit test values come from the ENDF-B/VIII.1 DT evaluation MT91. Q>0 so the threshold is zero.
      // The answers were generated using a Python script that evaluated the function on a
      // dense grid using the numpy linspace function, and integrated over regions using the
      // numpy trapezoid function.

      THEN( "an InterpolationTable can be constructed and members can be tested" ) {

        CHECK( 5 == chunk.numberPoints() );
        CHECK( 1 == chunk.numberRegions() );
        CHECK( 5 == chunk.x().size() );
        CHECK( 5 == chunk.y().size() );
        CHECK( 1 == chunk.boundaries().size() );
        CHECK( 1 == chunk.interpolants().size() );
        CHECK_THAT( 100., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 200., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 300., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 400., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 500., WithinRel( chunk.x()[4] ) );
        CHECK_THAT( 1.314e-60 , WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 4.7703e-43, WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2.6024e-35, WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1.0178e-30, WithinRel( chunk.y()[3] ) );
        CHECK_THAT( 1.3491e-27, WithinRel( chunk.y()[4] ) );
        CHECK( 4 == chunk.boundaries()[0] );
        CHECK( InterpolationType::CoulombPenetrability == chunk.interpolants()[0] );
        CHECK( 0 == chunk.threshold() );
        CHECK( false == chunk.isLinearised() );
        CHECK( true == chunk.isCurated() );
        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );

        CHECK_THAT( 3.6560950179562816e-53, WithinRel( chunk( 130.3030303030303 ) ) );
        CHECK_THAT( 1.5633677539389945e-46, WithinRel( chunk( 170.70707070707073 ) ) );

        CHECK_THAT( 2.1150433983771794e-26, WithinRel( chunk.integral(), 1e-5 ) );
      } // THEN

      THEN( "the CoulombPenetrabilityTable can be linearised" ) {

        // need to update the tolerance for these very small cross section values
        linearisation::ToleranceConvergence< double > convergence( 1e-5, 1e-60 );

        auto linear = chunk.linearise( convergence );

        CHECK( true == linear.isLinearised() );
        CHECK( 10665 == linear.numberPoints() );
        CHECK( 10665 == linear.x().size() );
        CHECK( 10665 == linear.y().size() );
        CHECK( 10664 == linear.boundaries()[0] );
        CHECK( InterpolationType::LinearLinear == linear.interpolants()[0] );
        CHECK( std::nullopt == linear.threshold() ); // <-- linearisation sets threshold to None
        CHECK_THAT( 3.6560950179562816e-53, WithinRel( linear( 130.3030303030303), 1e-5 ) );
        CHECK_THAT( 1.5633677539389945e-46, WithinRel( linear( 170.70707070707073 ), 1e-5 ) );
        CHECK_THAT( 2.1150640011019932e-26, WithinRel( linear.integral(), 1e-5 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

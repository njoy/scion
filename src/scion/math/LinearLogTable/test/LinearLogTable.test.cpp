// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/LinearLogTable.hpp"

// other includes
#include "utility/IteratorView.hpp"

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LinearLogTable = math::LinearLogTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LinearLogTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LinearLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LinearLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.41503749927884, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLogTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 7.3850580000476, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a HistogramTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral( 0. );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.44269504088896, WithinRel( cumulative[1] ) );
        CHECK_THAT( 5.9089985032654 , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.3850580000476 , WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of a LinearLogTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 16.248004728006, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a LinearLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 25 == linear.first.size() );
        CHECK( 25 == linear.second.size() );

        CHECK_THAT( 1.   , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.125, WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.25 , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.375, WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.5  , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.625, WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.75 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 1.875, WithinRel( linear.first[7] ) );
        CHECK_THAT( 2    , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.125, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.375, WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.625, WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 2.875, WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.   , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.125, WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.375, WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.625, WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.first[22] ) );
        CHECK_THAT( 3.875, WithinRel( linear.first[23] ) );
        CHECK_THAT( 4.   , WithinRel( linear.first[24] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.83007499855769, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.67807190511264, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.54056838136270, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3.41503749927884, WithinRel( linear.second[4] ) );
        CHECK_THAT( 3.29956028185891, WithinRel( linear.second[5] ) );
        CHECK_THAT( 3.19264507794240, WithinRel( linear.second[6] ) );
        CHECK_THAT( 3.09310940439148, WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[8] ) );
        CHECK_THAT( 2.85048128530886, WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.70951129135145, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.57616511633150, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.44966028678679, WithinRel( linear.second[12] ) );
        CHECK_THAT( 2.32932893596581, WithinRel( linear.second[13] ) );
        CHECK_THAT( 2.21459646033567, WithinRel( linear.second[14] ) );
        CHECK_THAT( 2.10496492439848, WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[16] ) );
        CHECK_THAT( 1.85810031827028, WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.72176678584324, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.59057916034679, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.46416306545103, WithinRel( linear.second[20] ) );
        CHECK_THAT( 1.34218354996644, WithinRel( linear.second[21] ) );
        CHECK_THAT( 1.22433973930853, WithinRel( linear.second[22] ) );
        CHECK_THAT( 1.11036036428687, WithinRel( linear.second[23] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[24] ) );
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
    } // WHEN

    WHEN( "the data is given explicitly using iterator views" ) {

      using View = njoy::utility::IteratorView< std::vector< double >::const_iterator >;

      const std::vector< double > xvalues= { 1., 2., 3., 4. };
      const std::vector< double > yvalues = { 4., 3., 2., 1. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LinearLogTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LinearLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LinearLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 1., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LinearLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 4., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 1., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 3.41503749927884, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 2.44966028678679, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 1.46416306545103, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LinearLogTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integral() << std::endl;
        CHECK_THAT( 7.3850580000476, WithinRel( chunk.integral() ) );
      } // THEN

      THEN( "the cumulative integral of a HistogramTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. ) << ' '
        //                                    << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        auto cumulative = chunk.cumulativeIntegral( 0. );
        CHECK( 4 == cumulative.size() );
        CHECK_THAT( 0.              , WithinRel( cumulative[0] ) );
        CHECK_THAT( 3.44269504088896, WithinRel( cumulative[1] ) );
        CHECK_THAT( 5.9089985032654 , WithinRel( cumulative[2] ) );
        CHECK_THAT( 7.3850580000476 , WithinRel( cumulative[3] ) );
      } // THEN

      THEN( "the first raw moment of a LinearLogTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 16.248004728006, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a LinearLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 25 == linear.first.size() );
        CHECK( 25 == linear.second.size() );

        CHECK_THAT( 1.   , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.125, WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.25 , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.375, WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.5  , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.625, WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.75 , WithinRel( linear.first[6] ) );
        CHECK_THAT( 1.875, WithinRel( linear.first[7] ) );
        CHECK_THAT( 2    , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.125, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.25 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.375, WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.5  , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.625, WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.75 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 2.875, WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.   , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.125, WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.25 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.375, WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.5  , WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.625, WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.75 , WithinRel( linear.first[22] ) );
        CHECK_THAT( 3.875, WithinRel( linear.first[23] ) );
        CHECK_THAT( 4.   , WithinRel( linear.first[24] ) );

        CHECK_THAT( 4.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 3.83007499855769, WithinRel( linear.second[1] ) );
        CHECK_THAT( 3.67807190511264, WithinRel( linear.second[2] ) );
        CHECK_THAT( 3.54056838136270, WithinRel( linear.second[3] ) );
        CHECK_THAT( 3.41503749927884, WithinRel( linear.second[4] ) );
        CHECK_THAT( 3.29956028185891, WithinRel( linear.second[5] ) );
        CHECK_THAT( 3.19264507794240, WithinRel( linear.second[6] ) );
        CHECK_THAT( 3.09310940439148, WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[8] ) );
        CHECK_THAT( 2.85048128530886, WithinRel( linear.second[9] ) );
        CHECK_THAT( 2.70951129135145, WithinRel( linear.second[10] ) );
        CHECK_THAT( 2.57616511633150, WithinRel( linear.second[11] ) );
        CHECK_THAT( 2.44966028678679, WithinRel( linear.second[12] ) );
        CHECK_THAT( 2.32932893596581, WithinRel( linear.second[13] ) );
        CHECK_THAT( 2.21459646033567, WithinRel( linear.second[14] ) );
        CHECK_THAT( 2.10496492439848, WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[16] ) );
        CHECK_THAT( 1.85810031827028, WithinRel( linear.second[17] ) );
        CHECK_THAT( 1.72176678584324, WithinRel( linear.second[18] ) );
        CHECK_THAT( 1.59057916034679, WithinRel( linear.second[19] ) );
        CHECK_THAT( 1.46416306545103, WithinRel( linear.second[20] ) );
        CHECK_THAT( 1.34218354996644, WithinRel( linear.second[21] ) );
        CHECK_THAT( 1.22433973930853, WithinRel( linear.second[22] ) );
        CHECK_THAT( 1.11036036428687, WithinRel( linear.second[23] ) );
        CHECK_THAT( 1.              , WithinRel( linear.second[24] ) );
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
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LinearLogTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( empty, empty ) );
        CHECK_THROWS( LinearLogTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LinearLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

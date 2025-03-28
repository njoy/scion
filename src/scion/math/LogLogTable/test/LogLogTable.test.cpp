// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "scion/math/LogLogTable.hpp"

// includes for test result generation
// #include <iostream>
// #include <iomanip>
// #include "scion/integration/GaussLegendre/64.hpp"

// other includes
#include "utility/IteratorView.hpp"

// convenience typedefs
using namespace njoy::scion;
template < typename X, typename Y = X,
           typename XContainer = std::vector< X >,
           typename YContainer = std::vector< Y > >
using LogLogTable = math::LogLogTable< X, Y, XContainer, YContainer >;
template < typename X > using IntervalDomain = math::IntervalDomain< X >;
template < typename X > using OpenDomain = math::OpenDomain< X >;
using InterpolationType = interpolation::InterpolationType;

SCENARIO( "LogLogTable" ) {

  GIVEN( "tabulated data" ) {

    WHEN( "the data is given explicitly using vectors" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 5., 4., 3., 2. };

      LogLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 5., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 4.388148142366000, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3.414296578519320, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.414154465691340, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integrate() << std::endl;
        CHECK_THAT( 10.3092587344326, WithinRel( chunk.integrate() ) );
      } // THEN

      THEN( "the first raw moment of a LogLinearTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 23.545310328628, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 24 == linear.first.size() );
        CHECK( 24 == linear.second.size() );

        CHECK_THAT( 1.    , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.125 , WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.25  , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.375 , WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.5   , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.625 , WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.75	, WithinRel( linear.first[6] ) );
        CHECK_THAT( 2.    , WithinRel( linear.first[7] ) );
        CHECK_THAT( 2.125 , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.25	, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.375 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.5	  , WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.625 , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.75  , WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.875 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 3.    , WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.125 , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.25  , WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.375 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.5   , WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.625 , WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.75  , WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.875 , WithinRel( linear.first[22] ) );
        CHECK_THAT( 4.    , WithinRel( linear.first[23] ) );

        CHECK_THAT( 5.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 4.81396102983755, WithinRel( linear.second[1] ) );
        CHECK_THAT( 4.65341674697485, WithinRel( linear.second[2] ) );
        CHECK_THAT( 4.51280408869662, WithinRel( linear.second[3] ) );
        CHECK_THAT( 4.38814814236600, WithinRel( linear.second[4] ) );
        CHECK_THAT( 4.27651876621215, WithinRel( linear.second[5] ) );
        CHECK_THAT( 4.17569941137597, WithinRel( linear.second[6] ) );
        CHECK_THAT( 4.              , WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.83159247811916, WithinRel( linear.second[8] ) );
        CHECK_THAT( 3.67931269616815, WithinRel( linear.second[9] ) );
        CHECK_THAT( 3.54084239458549, WithinRel( linear.second[10] ) );
        CHECK_THAT( 3.41429657851932, WithinRel( linear.second[11] ) );
        CHECK_THAT( 3.29812564084982, WithinRel( linear.second[12] ) );
        CHECK_THAT( 3.19104306545919, WithinRel( linear.second[13] ) );
        CHECK_THAT( 3.09197119793348, WithinRel( linear.second[14] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.83226549274327, WithinRel( linear.second[16] ) );
        CHECK_THAT( 2.67995077927182, WithinRel( linear.second[17] ) );
        CHECK_THAT( 2.54112379880362, WithinRel( linear.second[18] ) );
        CHECK_THAT( 2.41415446569134, WithinRel( linear.second[19] ) );
        CHECK_THAT( 2.29765875214808, WithinRel( linear.second[20] ) );
        CHECK_THAT( 2.19045463289248, WithinRel( linear.second[21] ) );
        CHECK_THAT( 2.09152707609899, WithinRel( linear.second[22] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[23] ) );
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
      const std::vector< double > yvalues = { 5., 4., 3., 2. };

      View x = njoy::utility::make_view( xvalues );
      View y = njoy::utility::make_view( yvalues );

      LogLogTable< double, double, View, View > chunk( std::move( x ), std::move( y ) );

      THEN( "a LogLogTable can be constructed and members can be tested" ) {

        CHECK( InterpolationType::LogLog == chunk.interpolation() );
        CHECK( 4 == chunk.numberPoints() );
        CHECK( 4 == chunk.x().size() );
        CHECK( 4 == chunk.y().size() );
        CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
        CHECK_THAT( 2., WithinRel( chunk.x()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.x()[2] ) );
        CHECK_THAT( 4., WithinRel( chunk.x()[3] ) );
        CHECK_THAT( 5., WithinRel( chunk.y()[0] ) );
        CHECK_THAT( 4., WithinRel( chunk.y()[1] ) );
        CHECK_THAT( 3., WithinRel( chunk.y()[2] ) );
        CHECK_THAT( 2., WithinRel( chunk.y()[3] ) );

        CHECK( true == std::holds_alternative< IntervalDomain< double > >( chunk.domain() ) );
      } // THEN

      THEN( "a LogLogTable can be evaluated" ) {

        // values of x in the x grid
        CHECK_THAT( 5., WithinRel( chunk( 1. ) ) );
        CHECK_THAT( 4., WithinRel( chunk( 2. ) ) );
        CHECK_THAT( 3., WithinRel( chunk( 3. ) ) );
        CHECK_THAT( 2., WithinRel( chunk( 4. ) ) );

        // values of x outside the x grid
        CHECK_THAT( 0., WithinRel( chunk( 0. ) ) );
        CHECK_THAT( 0., WithinRel( chunk( 5. ) ) );

        // values of x inside the x grid
        CHECK_THAT( 4.388148142366000, WithinRel( chunk( 1.5 ) ) );
        CHECK_THAT( 3.414296578519320, WithinRel( chunk( 2.5 ) ) );
        CHECK_THAT( 2.414154465691340, WithinRel( chunk( 3.5 ) ) );
      } // THEN

      THEN( "a LogLogTable can be integrated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // std::cout << std::setprecision(15) << integrator( chunk, 1.,  2. )
        //                                     + integrator( chunk, 2.,  3. )
        //                                     + integrator( chunk, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.integrate() << std::endl;
        CHECK_THAT( 10.3092587344326, WithinRel( chunk.integrate() ) );
      } // THEN

      THEN( "the first raw moment of a LogLinearTable can be calculated" ) {

        // generate test result using Gauss-Legendre quadrature
        // integration::GaussLegendre< 64, double > integrator{};
        // auto functor = [&chunk] ( auto&& x ) { return x * chunk( x ); };
        // std::cout << std::setprecision(15) << integrator( functor, 1.,  2. )
        //                                     + integrator( functor, 2.,  3. )
        //                                     + integrator( functor, 3.,  4. ) << std::endl;
        // std::cout << std::setprecision(15) << chunk.mean() << std::endl;
        CHECK_THAT( 23.545310328628, WithinRel( chunk.mean() ) );
      } // THEN

      THEN( "a LogLogTable can be linearised" ) {

        auto linear = chunk.linearise();

        CHECK( 24 == linear.first.size() );
        CHECK( 24 == linear.second.size() );

        CHECK_THAT( 1.    , WithinRel( linear.first[0] ) );
        CHECK_THAT( 1.125 , WithinRel( linear.first[1] ) );
        CHECK_THAT( 1.25  , WithinRel( linear.first[2] ) );
        CHECK_THAT( 1.375 , WithinRel( linear.first[3] ) );
        CHECK_THAT( 1.5   , WithinRel( linear.first[4] ) );
        CHECK_THAT( 1.625 , WithinRel( linear.first[5] ) );
        CHECK_THAT( 1.75	, WithinRel( linear.first[6] ) );
        CHECK_THAT( 2.    , WithinRel( linear.first[7] ) );
        CHECK_THAT( 2.125 , WithinRel( linear.first[8] ) );
        CHECK_THAT( 2.25	, WithinRel( linear.first[9] ) );
        CHECK_THAT( 2.375 , WithinRel( linear.first[10] ) );
        CHECK_THAT( 2.5	  , WithinRel( linear.first[11] ) );
        CHECK_THAT( 2.625 , WithinRel( linear.first[12] ) );
        CHECK_THAT( 2.75  , WithinRel( linear.first[13] ) );
        CHECK_THAT( 2.875 , WithinRel( linear.first[14] ) );
        CHECK_THAT( 3.    , WithinRel( linear.first[15] ) );
        CHECK_THAT( 3.125 , WithinRel( linear.first[16] ) );
        CHECK_THAT( 3.25  , WithinRel( linear.first[17] ) );
        CHECK_THAT( 3.375 , WithinRel( linear.first[18] ) );
        CHECK_THAT( 3.5   , WithinRel( linear.first[19] ) );
        CHECK_THAT( 3.625 , WithinRel( linear.first[20] ) );
        CHECK_THAT( 3.75  , WithinRel( linear.first[21] ) );
        CHECK_THAT( 3.875 , WithinRel( linear.first[22] ) );
        CHECK_THAT( 4.    , WithinRel( linear.first[23] ) );

        CHECK_THAT( 5.              , WithinRel( linear.second[0] ) );
        CHECK_THAT( 4.81396102983755, WithinRel( linear.second[1] ) );
        CHECK_THAT( 4.65341674697485, WithinRel( linear.second[2] ) );
        CHECK_THAT( 4.51280408869662, WithinRel( linear.second[3] ) );
        CHECK_THAT( 4.38814814236600, WithinRel( linear.second[4] ) );
        CHECK_THAT( 4.27651876621215, WithinRel( linear.second[5] ) );
        CHECK_THAT( 4.17569941137597, WithinRel( linear.second[6] ) );
        CHECK_THAT( 4.              , WithinRel( linear.second[7] ) );
        CHECK_THAT( 3.83159247811916, WithinRel( linear.second[8] ) );
        CHECK_THAT( 3.67931269616815, WithinRel( linear.second[9] ) );
        CHECK_THAT( 3.54084239458549, WithinRel( linear.second[10] ) );
        CHECK_THAT( 3.41429657851932, WithinRel( linear.second[11] ) );
        CHECK_THAT( 3.29812564084982, WithinRel( linear.second[12] ) );
        CHECK_THAT( 3.19104306545919, WithinRel( linear.second[13] ) );
        CHECK_THAT( 3.09197119793348, WithinRel( linear.second[14] ) );
        CHECK_THAT( 3.              , WithinRel( linear.second[15] ) );
        CHECK_THAT( 2.83226549274327, WithinRel( linear.second[16] ) );
        CHECK_THAT( 2.67995077927182, WithinRel( linear.second[17] ) );
        CHECK_THAT( 2.54112379880362, WithinRel( linear.second[18] ) );
        CHECK_THAT( 2.41415446569134, WithinRel( linear.second[19] ) );
        CHECK_THAT( 2.29765875214808, WithinRel( linear.second[20] ) );
        CHECK_THAT( 2.19045463289248, WithinRel( linear.second[21] ) );
        CHECK_THAT( 2.09152707609899, WithinRel( linear.second[22] ) );
        CHECK_THAT( 2.              , WithinRel( linear.second[23] ) );
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

    WHEN( "the data has an integration singularity" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      LogLogTable< double > chunk( std::move( x ), std::move( y ) );

      THEN( "this particular LogLogTable cannot be integrated" ) {

        CHECK_THROWS( chunk.integrate() );
      } // THEN
    }
  } // GIVEN

  GIVEN( "invalid data for a LogLogTable object" ) {

    WHEN( "there are not enough values in the x or y grid" ) {

      std::vector< double > empty = {};
      std::vector< double > one = { 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( empty, empty ) );
        CHECK_THROWS( LogLogTable< double >( one, one ) );
      } // THEN
    } // WHEN

    WHEN( "the x and y grid do not have the same number of points" ) {

      std::vector< double > x = { 1., 2., 3., 4. };
      std::vector< double > y = { 4., 3., 2. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid is not sorted" ) {

      std::vector< double > x = { 1., 3., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "the x grid has a duplicate point" ) {

      std::vector< double > x = { 1., 2., 2., 4. };
      std::vector< double > y = { 4., 3., 2., 1. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LogLogTable< double >( std::move( x ), std::move( y ) ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

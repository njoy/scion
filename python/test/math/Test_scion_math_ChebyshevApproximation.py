# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import ChebyshevApproximation
from scion.math import IntervalDomain

class Test_scion_math_ChebyshevApproximation( unittest.TestCase ) :
    """Unit test for the ChebyshevApproximation class."""

    def test_component( self ) :

        def verify_chunk_domain1( self, chunk ) :

            # verify content
            self.assertEqual( 10, chunk.order )

            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 0., chunk.coefficients[0] )
            self.assertAlmostEqual( 1., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -1., chunk.domain.lower_limit )
            self.assertEqual(  1., chunk.domain.upper_limit )

            # verify evaluation
            self.assertAlmostEqual( -1.0      , chunk( -1. ) )
            self.assertAlmostEqual( -0.9999999, chunk( -0.9999999 ) )
            self.assertAlmostEqual( -0.999999 , chunk( -0.999999 ) )
            self.assertAlmostEqual( -0.99999  , chunk( -0.99999 ) )
            self.assertAlmostEqual( -0.9999   , chunk( -0.9999 ) )
            self.assertAlmostEqual( -0.999    , chunk( -0.999 ) )
            self.assertAlmostEqual( -0.99     , chunk( -0.99 ) )
            self.assertAlmostEqual( -0.9      , chunk( -0.9 ) )
            self.assertAlmostEqual( -0.5      , chunk( -0.5 ) )
            self.assertAlmostEqual( -0.05     , chunk( -0.05 ) )
            self.assertAlmostEqual( -0.005    , chunk( -0.005 ) )
            self.assertAlmostEqual( -0.0005   , chunk( -0.0005 ) )
            self.assertAlmostEqual( -0.00005  , chunk( -0.00005 ) )
            self.assertAlmostEqual( -0.000005 , chunk( -0.000005 ) )
            self.assertAlmostEqual( -0.0000005, chunk( -0.0000005 ) )
            self.assertAlmostEqual(  0.0      , chunk(  0. ) )
            self.assertAlmostEqual( +0.0000005, chunk(  0.0000005 ) )
            self.assertAlmostEqual( +0.000005 , chunk(  0.000005 ) )
            self.assertAlmostEqual( +0.00005  , chunk(  0.00005 ) )
            self.assertAlmostEqual( +0.0005   , chunk(  0.0005 ) )
            self.assertAlmostEqual( +0.005    , chunk(  0.005 ) )
            self.assertAlmostEqual( +0.05     , chunk(  0.05 ) )
            self.assertAlmostEqual( +0.5      , chunk(  0.5 ) )
            self.assertAlmostEqual( +0.9      , chunk(  0.9 ) )
            self.assertAlmostEqual( +0.99     , chunk(  0.99 ) )
            self.assertAlmostEqual( +0.999    , chunk(  0.999 ) )
            self.assertAlmostEqual( +0.9999   , chunk(  0.9999 ) )
            self.assertAlmostEqual( +0.99999  , chunk(  0.99999 ) )
            self.assertAlmostEqual( +0.999999 , chunk(  0.999999 ) )
            self.assertAlmostEqual( +0.9999999, chunk(  0.9999999 ) )
            self.assertAlmostEqual( +1.0      , chunk(  1. ) )

            # verify arithmetic operators
            chunk += 2.
            self.assertEqual( 10, chunk.order )
            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 2., chunk.coefficients[0] )
            self.assertAlmostEqual( 1., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )
            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -1., chunk.domain.lower_limit )
            self.assertEqual(  1., chunk.domain.upper_limit )

            chunk -= 2.
            self.assertEqual( 10, chunk.order )
            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 0., chunk.coefficients[0] )
            self.assertAlmostEqual( 1., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )
            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -1., chunk.domain.lower_limit )
            self.assertEqual(  1., chunk.domain.upper_limit )

        def verify_chunk_domain2( self, chunk ) :

            # verify content
            self.assertEqual( 10, chunk.order )

            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 1., chunk.coefficients[0] )
            self.assertAlmostEqual( 3., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -2., chunk.domain.lower_limit )
            self.assertEqual(  4., chunk.domain.upper_limit )

            # verify evaluation
            self.assertAlmostEqual( -1.0      , chunk( -1. ) )
            self.assertAlmostEqual( -0.9999999, chunk( -0.9999999 ) )
            self.assertAlmostEqual( -0.999999 , chunk( -0.999999 ) )
            self.assertAlmostEqual( -0.99999  , chunk( -0.99999 ) )
            self.assertAlmostEqual( -0.9999   , chunk( -0.9999 ) )
            self.assertAlmostEqual( -0.999    , chunk( -0.999 ) )
            self.assertAlmostEqual( -0.99     , chunk( -0.99 ) )
            self.assertAlmostEqual( -0.9      , chunk( -0.9 ) )
            self.assertAlmostEqual( -0.5      , chunk( -0.5 ) )
            self.assertAlmostEqual( -0.05     , chunk( -0.05 ) )
            self.assertAlmostEqual( -0.005    , chunk( -0.005 ) )
            self.assertAlmostEqual( -0.0005   , chunk( -0.0005 ) )
            self.assertAlmostEqual( -0.00005  , chunk( -0.00005 ) )
            self.assertAlmostEqual( -0.000005 , chunk( -0.000005 ) )
            self.assertAlmostEqual( -0.0000005, chunk( -0.0000005 ) )
            self.assertAlmostEqual(  0.0      , chunk(  0. ) )
            self.assertAlmostEqual( +0.0000005, chunk(  0.0000005 ) )
            self.assertAlmostEqual( +0.000005 , chunk(  0.000005 ) )
            self.assertAlmostEqual( +0.00005  , chunk(  0.00005 ) )
            self.assertAlmostEqual( +0.0005   , chunk(  0.0005 ) )
            self.assertAlmostEqual( +0.005    , chunk(  0.005 ) )
            self.assertAlmostEqual( +0.05     , chunk(  0.05 ) )
            self.assertAlmostEqual( +0.5      , chunk(  0.5 ) )
            self.assertAlmostEqual( +0.9      , chunk(  0.9 ) )
            self.assertAlmostEqual( +0.99     , chunk(  0.99 ) )
            self.assertAlmostEqual( +0.999    , chunk(  0.999 ) )
            self.assertAlmostEqual( +0.9999   , chunk(  0.9999 ) )
            self.assertAlmostEqual( +0.99999  , chunk(  0.99999 ) )
            self.assertAlmostEqual( +0.999999 , chunk(  0.999999 ) )
            self.assertAlmostEqual( +0.9999999, chunk(  0.9999999 ) )
            self.assertAlmostEqual( +1.0      , chunk(  1. ) )

            # verify arithmetic operators
            chunk += 2.
            self.assertEqual( 10, chunk.order )
            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 3., chunk.coefficients[0] )
            self.assertAlmostEqual( 3., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )
            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -2., chunk.domain.lower_limit )
            self.assertEqual(  4., chunk.domain.upper_limit )

            chunk -= 2.
            self.assertEqual( 10, chunk.order )
            self.assertEqual( 11, len( chunk.coefficients ) )
            self.assertAlmostEqual( 1., chunk.coefficients[0] )
            self.assertAlmostEqual( 3., chunk.coefficients[1] )
            self.assertAlmostEqual( 0., chunk.coefficients[2] )
            self.assertAlmostEqual( 0., chunk.coefficients[3] )
            self.assertAlmostEqual( 0., chunk.coefficients[4] )
            self.assertAlmostEqual( 0., chunk.coefficients[5] )
            self.assertAlmostEqual( 0., chunk.coefficients[6] )
            self.assertAlmostEqual( 0., chunk.coefficients[7] )
            self.assertAlmostEqual( 0., chunk.coefficients[8] )
            self.assertAlmostEqual( 0., chunk.coefficients[9] )
            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )
            self.assertEqual( -2., chunk.domain.lower_limit )
            self.assertEqual(  4., chunk.domain.upper_limit )

        # test function : f(x) = x
        def function( x ) : return x

        # the function is approximated on [-1,1]
        chunk = ChebyshevApproximation( lower = -1., upper = 1.,
                                        function = function, order = 10 )

        verify_chunk_domain1( self, chunk )

        # the function is approximated on [-2,4]
        chunk = ChebyshevApproximation( lower = -2., upper = 4.,
                                        function = function, order = 10 )

        verify_chunk_domain2( self, chunk )

if __name__ == '__main__' :

    unittest.main()

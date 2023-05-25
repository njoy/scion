# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LegendreSeries
from scion.math import IntervalDomain

class Test_scion_math_LegendreSeries( unittest.TestCase ) :
    """Unit test for the LegendreSeries class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -10.33333333, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.6       , chunk.coefficients[1] )
            self.assertAlmostEqual(  -4.66666667, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.4       , chunk.coefficients[3] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )

            # verify evaluation
            self.assertAlmostEqual(  -8.0, chunk( x =  0. ) )
            self.assertAlmostEqual(   0.0, chunk( x =  1. ) )
            self.assertAlmostEqual( -30.0, chunk( x = -1. ) )

            # verify derivative
            first = chunk.derivative()
            second = first.derivative()
            third = second.derivative()
            fourth = third.derivative()

            self.assertEqual( 2, first.order )
            self.assertEqual( 3, len( first.coefficients ) )
            self.assertAlmostEqual(  15., first.coefficients[0] )
            self.assertAlmostEqual( -14., first.coefficients[1] )
            self.assertAlmostEqual(   2., first.coefficients[2] )

            self.assertEqual( 1, second.order )
            self.assertEqual( 2, len( second.coefficients ) )
            self.assertAlmostEqual( -14., second.coefficients[0] )
            self.assertAlmostEqual(   6., second.coefficients[1] )

            self.assertEqual( 0, third.order )
            self.assertEqual( 1, len( third.coefficients ) )
            self.assertAlmostEqual( 6., third.coefficients[0] )

            self.assertEqual( 0, fourth.order )
            self.assertEqual( 1, len( fourth.coefficients ) )
            self.assertAlmostEqual( 0., fourth.coefficients[0] )

            # verify primitive
            primitive = chunk.primitive()

            self.assertEqual( 4, primitive.order )
            self.assertEqual( 5, len( primitive.coefficients ) )
            self.assertAlmostEqual( 2.3833333333333333, primitive.coefficients[0] )
            self.assertAlmostEqual( -9.4, primitive.coefficients[1] )
            self.assertAlmostEqual(  4.809523809523809, primitive.coefficients[2] )
            self.assertAlmostEqual( -0.933333333333333, primitive.coefficients[3] )
            self.assertAlmostEqual(  0.057142857142857, primitive.coefficients[4] )

            # verify roots
            roots = chunk.roots()
            self.assertEqual( 3, len( roots ) )
            self.assertAlmostEqual( 1.0, roots[0] )
            self.assertAlmostEqual( 2.0, roots[1] )
            self.assertAlmostEqual( 4.0, roots[2] )

            roots = chunk.roots( -8. )
            self.assertEqual( 1, len( roots ) )
            self.assertAlmostEqual( 0.0, roots[0] )

        # the data is given explicitly
        chunk = LegendreSeries( coefficients = [ -31./3., 73./5., -14./3., 2./5. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = LegendreSeries( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()

# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import ChebyshevSeries
from scion.math import IntervalDomain

class Test_scion_math_ChebyshevSeries( unittest.TestCase ) :
    """Unit test for the ChebyshevSeries class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )

            # verify evaluation
            self.assertAlmostEqual(  -8.0, chunk( x =  0. ) )
            self.assertAlmostEqual(   0.0, chunk( x =  1. ) )
            self.assertAlmostEqual( -30.0, chunk( x = -1. ) )

            # verify roots
            roots = chunk.roots()
            self.assertEqual( 3, len( roots ) )
            self.assertAlmostEqual( 1.0, roots[0] )
            self.assertAlmostEqual( 2.0, roots[1] )
            self.assertAlmostEqual( 4.0, roots[2] )

            roots = chunk.roots( -8. )
            self.assertEqual( 1, len( roots ) )
            self.assertAlmostEqual( 0.0, roots[0] )

            # verify derivative
            first = chunk.derivative()
            second = first.derivative()
            third = second.derivative()
            fourth = third.derivative()

            self.assertEqual( 2, first.order )
            self.assertEqual( 3, len( first.coefficients ) )
            self.assertAlmostEqual(  15.5, first.coefficients[0] )
            self.assertAlmostEqual( -14.0, first.coefficients[1] )
            self.assertAlmostEqual(   1.5, first.coefficients[2] )

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
            self.assertAlmostEqual( 3.59375, primitive.coefficients[0] )
            self.assertAlmostEqual( -9.75, primitive.coefficients[1] )
            self.assertAlmostEqual(  3.625, primitive.coefficients[2] )
            self.assertAlmostEqual( -0.5833333333333334, primitive.coefficients[3] )
            self.assertAlmostEqual(  0.03125, primitive.coefficients[4] )

            primitive = chunk.primitive( left = -1. )

            self.assertEqual( 4, primitive.order )
            self.assertEqual( 5, len( primitive.coefficients ) )
            self.assertAlmostEqual( -13.989583333333332, primitive.coefficients[0] )
            self.assertAlmostEqual( -9.75, primitive.coefficients[1] )
            self.assertAlmostEqual(  3.625, primitive.coefficients[2] )
            self.assertAlmostEqual( -0.5833333333333334, primitive.coefficients[3] )
            self.assertAlmostEqual(  0.03125, primitive.coefficients[4] )

            # verify arithmetic operators
            small = ChebyshevSeries( [ 3., 0., 1. ] )
            equal = ChebyshevSeries( [ 3., 0., 0., 1. ] )
            large = ChebyshevSeries( [ 3., 0., 0., 0., 1. ] )
            result = ChebyshevSeries( [ 0. ] )

            chunk += 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -9.50, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.75, chunk.coefficients[1] )
            self.assertAlmostEqual( -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.25, chunk.coefficients[3] )

            chunk -= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            chunk += small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8.50, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.75, chunk.coefficients[1] )
            self.assertAlmostEqual( -2.50, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.25, chunk.coefficients[3] )

            chunk -= small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            chunk += equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8.50, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.75, chunk.coefficients[1] )
            self.assertAlmostEqual( -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(  1.25, chunk.coefficients[3] )

            chunk -= equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            chunk += large
            self.assertEqual( 4, chunk.order )
            self.assertEqual( 5, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8.50, chunk.coefficients[0] )
            self.assertAlmostEqual( 14.75, chunk.coefficients[1] )
            self.assertAlmostEqual( -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(  0.25, chunk.coefficients[3] )
            self.assertAlmostEqual(  1.00, chunk.coefficients[4] )

            chunk -= large
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            chunk *= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -23.0, chunk.coefficients[0] )
            self.assertAlmostEqual(  29.5, chunk.coefficients[1] )
            self.assertAlmostEqual(  -7.0, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.5, chunk.coefficients[3] )

            chunk /= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -11.50, chunk.coefficients[0] )
            self.assertAlmostEqual(  14.75, chunk.coefficients[1] )
            self.assertAlmostEqual(  -3.50, chunk.coefficients[2] )
            self.assertAlmostEqual(   0.25, chunk.coefficients[3] )

            result = chunk + 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -9.50, result.coefficients[0] )
            self.assertAlmostEqual( 14.75, result.coefficients[1] )
            self.assertAlmostEqual( -3.50, result.coefficients[2] )
            self.assertAlmostEqual(  0.25, result.coefficients[3] )

            result = chunk - 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -13.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -3.50, result.coefficients[2] )
            self.assertAlmostEqual(   0.25, result.coefficients[3] )

            result = chunk * 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -23.0, result.coefficients[0] )
            self.assertAlmostEqual(  29.5, result.coefficients[1] )
            self.assertAlmostEqual(  -7.0, result.coefficients[2] )
            self.assertAlmostEqual(   0.5, result.coefficients[3] )

            result = chunk / 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -5.750, result.coefficients[0] )
            self.assertAlmostEqual(  7.375, result.coefficients[1] )
            self.assertAlmostEqual( -1.750, result.coefficients[2] )
            self.assertAlmostEqual(  0.125, result.coefficients[3] )

            result = chunk + small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual(  -8.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -2.50, result.coefficients[2] )
            self.assertAlmostEqual(   0.25, result.coefficients[3] )

            result = chunk - small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -14.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -4.50, result.coefficients[2] )
            self.assertAlmostEqual(   0.25, result.coefficients[3] )

            result = chunk + equal
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual(  -8.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -3.50, result.coefficients[2] )
            self.assertAlmostEqual(   1.25, result.coefficients[3] )

            result = chunk - equal
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -14.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -3.50, result.coefficients[2] )
            self.assertAlmostEqual(  -0.75, result.coefficients[3] )

            result = chunk + large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual(  -8.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -3.50, result.coefficients[2] )
            self.assertAlmostEqual(   0.25, result.coefficients[3] )
            self.assertAlmostEqual(   1.00, result.coefficients[4] )

            result = chunk - large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual( -14.50, result.coefficients[0] )
            self.assertAlmostEqual(  14.75, result.coefficients[1] )
            self.assertAlmostEqual(  -3.50, result.coefficients[2] )
            self.assertAlmostEqual(   0.25, result.coefficients[3] )
            self.assertAlmostEqual(  -1.00, result.coefficients[4] )

        # the data is given explicitly
        chunk = ChebyshevSeries( coefficients = [ -23./2., 59./4., -7./2., 1./4. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = ChebyshevSeries( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()

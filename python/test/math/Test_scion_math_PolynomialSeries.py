# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import PolynomialSeries
from scion.math import IntervalDomain

class Test_scion_math_PolynomialSeries( unittest.TestCase ) :
    """Unit test for the PolynomialSeries class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

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
            self.assertAlmostEqual(  14., first.coefficients[0] )
            self.assertAlmostEqual( -14., first.coefficients[1] )
            self.assertAlmostEqual(   3., first.coefficients[2] )
            self.assertEqual( True, isinstance( first.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., first.domain.lower_limit )
            self.assertAlmostEqual(  1., first.domain.upper_limit )

            self.assertEqual( 1, second.order )
            self.assertEqual( 2, len( second.coefficients ) )
            self.assertAlmostEqual( -14., second.coefficients[0] )
            self.assertAlmostEqual(   6., second.coefficients[1] )
            self.assertEqual( True, isinstance( second.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., second.domain.lower_limit )
            self.assertAlmostEqual(  1., second.domain.upper_limit )

            self.assertEqual( 0, third.order )
            self.assertEqual( 1, len( third.coefficients ) )
            self.assertAlmostEqual( 6., third.coefficients[0] )
            self.assertEqual( True, isinstance( third.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., third.domain.lower_limit )
            self.assertAlmostEqual(  1., third.domain.upper_limit )

            self.assertEqual( 0, fourth.order )
            self.assertEqual( 1, len( fourth.coefficients ) )
            self.assertAlmostEqual( 0., fourth.coefficients[0] )
            self.assertEqual( True, isinstance( fourth.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., fourth.domain.lower_limit )
            self.assertAlmostEqual(  1., fourth.domain.upper_limit )

            # verify primitive
            primitive = chunk.primitive()

            self.assertEqual( 4, primitive.order )
            self.assertEqual( 5, len( primitive.coefficients ) )
            self.assertAlmostEqual(   0., primitive.coefficients[0] )
            self.assertAlmostEqual(  -8., primitive.coefficients[1] )
            self.assertAlmostEqual(   7., primitive.coefficients[2] )
            self.assertAlmostEqual(  -7. / 3., primitive.coefficients[3] )
            self.assertAlmostEqual(   1. / 4., primitive.coefficients[4] )
            self.assertEqual( True, isinstance( primitive.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., primitive.domain.lower_limit )
            self.assertAlmostEqual(  1., primitive.domain.upper_limit )

            primitive = chunk.primitive( left = -1. )

            self.assertEqual( 4, primitive.order )
            self.assertEqual( 5, len( primitive.coefficients ) )
            self.assertAlmostEqual( -211. / 12., primitive.coefficients[0] )
            self.assertAlmostEqual(  -8., primitive.coefficients[1] )
            self.assertAlmostEqual(   7., primitive.coefficients[2] )
            self.assertAlmostEqual(  -7. / 3., primitive.coefficients[3] )
            self.assertAlmostEqual(   1. / 4., primitive.coefficients[4] )
            self.assertEqual( True, isinstance( primitive.domain, IntervalDomain ) )
            self.assertAlmostEqual( -1., primitive.domain.lower_limit )
            self.assertAlmostEqual(  1., primitive.domain.upper_limit )

            # verify roots
            roots = chunk.roots()
            self.assertEqual( 3, len( roots ) )
            self.assertAlmostEqual( 1.0, roots[0] )
            self.assertAlmostEqual( 2.0, roots[1] )
            self.assertAlmostEqual( 4.0, roots[2] )

            roots = chunk.roots( -8. )
            self.assertEqual( 1, len( roots ) )
            self.assertAlmostEqual( 0.0, roots[0] )

            # verify arithmetic operators
            small = PolynomialSeries( [ 3., 0., 1. ] )
            equal = PolynomialSeries( [ 3., 0., 0., 1. ] )
            large = PolynomialSeries( [ 3., 0., 0., 0., 1. ] )
            result = PolynomialSeries( [ 0. ] )

            chunk += 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -6., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk -= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk += small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -5., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -6., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk -= small
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk += equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -5., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  2., chunk.coefficients[3] )

            chunk -= equal
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk += large
            self.assertEqual( 4, chunk.order )
            self.assertEqual( 5, len( chunk.coefficients ) )
            self.assertAlmostEqual( -5., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )
            self.assertAlmostEqual(  1., chunk.coefficients[4] )

            chunk -= large
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            chunk *= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -16., chunk.coefficients[0] )
            self.assertAlmostEqual(  28., chunk.coefficients[1] )
            self.assertAlmostEqual( -14., chunk.coefficients[2] )
            self.assertAlmostEqual(   2., chunk.coefficients[3] )

            chunk /= 2.
            self.assertEqual( 3, chunk.order )
            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( -8., chunk.coefficients[0] )
            self.assertAlmostEqual( 14., chunk.coefficients[1] )
            self.assertAlmostEqual( -7., chunk.coefficients[2] )
            self.assertAlmostEqual(  1., chunk.coefficients[3] )

            result = chunk + 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -6., result.coefficients[0] )
            self.assertAlmostEqual( 14., result.coefficients[1] )
            self.assertAlmostEqual( -7., result.coefficients[2] )
            self.assertAlmostEqual(  1., result.coefficients[3] )

            result = chunk - 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -10., result.coefficients[0] )
            self.assertAlmostEqual(  14., result.coefficients[1] )
            self.assertAlmostEqual(  -7., result.coefficients[2] )
            self.assertAlmostEqual(   1., result.coefficients[3] )

        # the data is given explicitly
        chunk = PolynomialSeries( lower = -1., upper = 1.,
                                  coefficients = [ -8., 14., -7., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = PolynomialSeries( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()

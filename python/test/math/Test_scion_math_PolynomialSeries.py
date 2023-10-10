# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import PolynomialSeries
from scion.math import IntervalDomain
from scion.math import OpenDomain
from scion.linearisation import ToleranceConvergence
from scion.interpolation import InterpolationType

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

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( -1. ) )
            self.assertEqual( True, chunk.is_inside(  0. ) )
            self.assertEqual( True, chunk.is_inside(  1. ) )

            self.assertEqual( False, chunk.is_contained( -1. ) )
            self.assertEqual( True, chunk.is_contained(  0. ) )
            self.assertEqual( False, chunk.is_contained(  1. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( -1., 1. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 1. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            convergence = ToleranceConvergence( 0.01 )
            linear = chunk.linearise( convergence )

            self.assertEqual( 21, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 21, len( linear.x ) )
            self.assertEqual( 21, len( linear.y ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 20, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( -1.0      , linear.x[0] )
            self.assertAlmostEqual( -0.75     , linear.x[1] )
            self.assertAlmostEqual( -0.5      , linear.x[2] )
            self.assertAlmostEqual( -0.25     , linear.x[3] )
            self.assertAlmostEqual( -0.125    , linear.x[4] )
            self.assertAlmostEqual(  0.0      , linear.x[5] )
            self.assertAlmostEqual(  0.125    , linear.x[6] )
            self.assertAlmostEqual(  0.25     , linear.x[7] )
            self.assertAlmostEqual(  0.375    , linear.x[8] )
            self.assertAlmostEqual(  0.5      , linear.x[9] )
            self.assertAlmostEqual(  0.625    , linear.x[10] )
            self.assertAlmostEqual(  0.6875   , linear.x[11] )
            self.assertAlmostEqual(  0.75     , linear.x[12] )
            self.assertAlmostEqual(  0.8125   , linear.x[13] )
            self.assertAlmostEqual(  0.875    , linear.x[14] )
            self.assertAlmostEqual(  0.90625  , linear.x[15] )
            self.assertAlmostEqual(  0.9375   , linear.x[16] )
            self.assertAlmostEqual(  0.96875  , linear.x[17] )
            self.assertAlmostEqual(  0.984375 , linear.x[18] )
            self.assertAlmostEqual(  0.9921875, linear.x[19] )
            self.assertAlmostEqual(  1.0      , linear.x[20] )

            self.assertAlmostEqual( -30.0             , linear.y[0] )
            self.assertAlmostEqual( -22.859375        , linear.y[1] )
            self.assertAlmostEqual( -16.875           , linear.y[2] )
            self.assertAlmostEqual( -11.953125        , linear.y[3] )
            self.assertAlmostEqual( -9.861328125      , linear.y[4] )
            self.assertAlmostEqual( -8.0              , linear.y[5] )
            self.assertAlmostEqual( -6.357421875      , linear.y[6] )
            self.assertAlmostEqual( -4.921875         , linear.y[7] )
            self.assertAlmostEqual( -3.681640625      , linear.y[8] )
            self.assertAlmostEqual( -2.625            , linear.y[9] )
            self.assertAlmostEqual( -1.740234375      , linear.y[10] )
            self.assertAlmostEqual( -1.358642578125   , linear.y[11] )
            self.assertAlmostEqual( -1.015625         , linear.y[12] )
            self.assertAlmostEqual( -0.709716796875   , linear.y[13] )
            self.assertAlmostEqual( -0.439453125      , linear.y[14] )
            self.assertAlmostEqual( -0.317230224609375, linear.y[15] )
            self.assertAlmostEqual( -0.203369140625   , linear.y[16] )
            self.assertAlmostEqual( -0.097686767578125, linear.y[17] )
            self.assertAlmostEqual( -0.047855377197266, linear.y[18] )
            self.assertAlmostEqual( -0.023682117462158, linear.y[19] )
            self.assertAlmostEqual(  0.0              , linear.y[20] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators
            small = PolynomialSeries( [ 3., 0., 1. ] )
            equal = PolynomialSeries( [ 3., 0., 0., 1. ] )
            large = PolynomialSeries( [ 3., 0., 0., 0., 1. ] )

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

            result = chunk * 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -16., result.coefficients[0] )
            self.assertAlmostEqual(  28., result.coefficients[1] )
            self.assertAlmostEqual( -14., result.coefficients[2] )
            self.assertAlmostEqual(   2., result.coefficients[3] )

            result = chunk / 2.
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -4.0, result.coefficients[0] )
            self.assertAlmostEqual(  7.0, result.coefficients[1] )
            self.assertAlmostEqual( -3.5, result.coefficients[2] )
            self.assertAlmostEqual(  0.5, result.coefficients[3] )

            result = chunk + small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -5., result.coefficients[0] )
            self.assertAlmostEqual( 14., result.coefficients[1] )
            self.assertAlmostEqual( -6., result.coefficients[2] )
            self.assertAlmostEqual(  1., result.coefficients[3] )

            result = chunk - small
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -11., result.coefficients[0] )
            self.assertAlmostEqual(  14., result.coefficients[1] )
            self.assertAlmostEqual(  -8., result.coefficients[2] )
            self.assertAlmostEqual(   1., result.coefficients[3] )

            result = chunk + equal
            self.assertEqual( 3, result.order )
            self.assertEqual( 4, len( result.coefficients ) )
            self.assertAlmostEqual( -5., result.coefficients[0] )
            self.assertAlmostEqual( 14., result.coefficients[1] )
            self.assertAlmostEqual( -7., result.coefficients[2] )
            self.assertAlmostEqual(  2., result.coefficients[3] )

            result = chunk - equal
            self.assertEqual( 2, result.order )
            self.assertEqual( 3, len( result.coefficients ) )
            self.assertAlmostEqual( -11., result.coefficients[0] )
            self.assertAlmostEqual(  14., result.coefficients[1] )
            self.assertAlmostEqual(  -7., result.coefficients[2] )

            result = chunk + large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual( -5., result.coefficients[0] )
            self.assertAlmostEqual( 14., result.coefficients[1] )
            self.assertAlmostEqual( -7., result.coefficients[2] )
            self.assertAlmostEqual(  1., result.coefficients[3] )
            self.assertAlmostEqual(  1., result.coefficients[4] )

            result = chunk - large
            self.assertEqual( 4, result.order )
            self.assertEqual( 5, len( result.coefficients ) )
            self.assertAlmostEqual( -11., result.coefficients[0] )
            self.assertAlmostEqual(  14., result.coefficients[1] )
            self.assertAlmostEqual(  -7., result.coefficients[2] )
            self.assertAlmostEqual(   1., result.coefficients[3] )
            self.assertAlmostEqual(  -1., result.coefficients[4] )

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

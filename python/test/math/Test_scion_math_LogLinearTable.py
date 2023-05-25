# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LogLinearTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_LogLinearTable( unittest.TestCase ) :
    """Unit test for the LogLinearTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.LogLinear, chunk.interpolation )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk.evaluate( x = 1. ) )
            self.assertAlmostEqual( 3., chunk.evaluate( x = 2. ) )
            self.assertAlmostEqual( 2., chunk.evaluate( x = 3. ) )
            self.assertAlmostEqual( 1., chunk.evaluate( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.464101615, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.414213562, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 21, len( linear.x ) )
            self.assertEqual( 21, len( linear.y ) )

            self.assertAlmostEqual( 1.   , linear.x[0] )
            self.assertAlmostEqual( 1.25 , linear.x[1] )
            self.assertAlmostEqual( 1.5  , linear.x[2] )
            self.assertAlmostEqual( 1.75 , linear.x[3] )
            self.assertAlmostEqual( 2    , linear.x[4] )
            self.assertAlmostEqual( 2.125, linear.x[5] )
            self.assertAlmostEqual( 2.25 , linear.x[6] )
            self.assertAlmostEqual( 2.375, linear.x[7] )
            self.assertAlmostEqual( 2.5  , linear.x[8] )
            self.assertAlmostEqual( 2.625, linear.x[9] )
            self.assertAlmostEqual( 2.75 , linear.x[10] )
            self.assertAlmostEqual( 2.875, linear.x[11] )
            self.assertAlmostEqual( 3.   , linear.x[12] )
            self.assertAlmostEqual( 3.125, linear.x[13] )
            self.assertAlmostEqual( 3.25 , linear.x[14] )
            self.assertAlmostEqual( 3.375, linear.x[15] )
            self.assertAlmostEqual( 3.5  , linear.x[16] )
            self.assertAlmostEqual( 3.625, linear.x[17] )
            self.assertAlmostEqual( 3.75 , linear.x[18] )
            self.assertAlmostEqual( 3.875, linear.x[19] )
            self.assertAlmostEqual( 4.   , linear.x[20] )

            self.assertAlmostEqual( 4.         , linear.y[0] )
            self.assertAlmostEqual( 3.722419436, linear.y[1] )
            self.assertAlmostEqual( 3.464101615, linear.y[2] )
            self.assertAlmostEqual( 3.223709795, linear.y[3] )
            self.assertAlmostEqual( 3          , linear.y[4] )
            self.assertAlmostEqual( 2.851739475, linear.y[5] )
            self.assertAlmostEqual( 2.710806011, linear.y[6] )
            self.assertAlmostEqual( 2.576837503, linear.y[7] )
            self.assertAlmostEqual( 2.449489743, linear.y[8] )
            self.assertAlmostEqual( 2.328435531, linear.y[9] )
            self.assertAlmostEqual( 2.213363839, linear.y[10] )
            self.assertAlmostEqual( 2.103979011, linear.y[11] )
            self.assertAlmostEqual( 2.         , linear.y[12] )
            self.assertAlmostEqual( 1.834008086, linear.y[13] )
            self.assertAlmostEqual( 1.681792831, linear.y[14] )
            self.assertAlmostEqual( 1.542210825, linear.y[15] )
            self.assertAlmostEqual( 1.414213562, linear.y[16] )
            self.assertAlmostEqual( 1.296839555, linear.y[17] )
            self.assertAlmostEqual( 1.189207115, linear.y[18] )
            self.assertAlmostEqual( 1.090507733, linear.y[19] )
            self.assertAlmostEqual( 1.         , linear.y[20] )

        # the data is given explicitly
        chunk = LogLinearTable( x = [ 1., 2., 3., 4. ],
                                y = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = LogLinearTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = LogLinearTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = LogLinearTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = LogLinearTable( x = [ 1., 3., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

        # the x grid has a duplicate point
        with self.assertRaises( Exception ) :

            chunk = LogLinearTable( x = [ 1., 2., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

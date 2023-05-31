# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LinearLogTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_LinearLogTable( unittest.TestCase ) :
    """Unit test for the LinearLogTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolation )
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
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 3., chunk( x = 2. ) )
            self.assertAlmostEqual( 2., chunk( x = 3. ) )
            self.assertAlmostEqual( 1., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.415037499, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.464163065, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 25, len( linear[0] ) )
            self.assertEqual( 25, len( linear[1] ) )

            self.assertAlmostEqual( 1.   , linear[0][0] )
            self.assertAlmostEqual( 1.125, linear[0][1] )
            self.assertAlmostEqual( 1.25 , linear[0][2] )
            self.assertAlmostEqual( 1.375, linear[0][3] )
            self.assertAlmostEqual( 1.5  , linear[0][4] )
            self.assertAlmostEqual( 1.625, linear[0][5] )
            self.assertAlmostEqual( 1.75 , linear[0][6] )
            self.assertAlmostEqual( 1.875, linear[0][7] )
            self.assertAlmostEqual( 2    , linear[0][8] )
            self.assertAlmostEqual( 2.125, linear[0][9] )
            self.assertAlmostEqual( 2.25 , linear[0][10] )
            self.assertAlmostEqual( 2.375, linear[0][11] )
            self.assertAlmostEqual( 2.5  , linear[0][12] )
            self.assertAlmostEqual( 2.625, linear[0][13] )
            self.assertAlmostEqual( 2.75 , linear[0][14] )
            self.assertAlmostEqual( 2.875, linear[0][15] )
            self.assertAlmostEqual( 3.   , linear[0][16] )
            self.assertAlmostEqual( 3.125, linear[0][17] )
            self.assertAlmostEqual( 3.25 , linear[0][18] )
            self.assertAlmostEqual( 3.375, linear[0][19] )
            self.assertAlmostEqual( 3.5  , linear[0][20] )
            self.assertAlmostEqual( 3.625, linear[0][21] )
            self.assertAlmostEqual( 3.75 , linear[0][22] )
            self.assertAlmostEqual( 3.875, linear[0][23] )
            self.assertAlmostEqual( 4.   , linear[0][24] )

            self.assertAlmostEqual( 4.         , linear[1][0] )
            self.assertAlmostEqual( 3.830074999, linear[1][1] )
            self.assertAlmostEqual( 3.678071905, linear[1][2] )
            self.assertAlmostEqual( 3.540568381, linear[1][3] )
            self.assertAlmostEqual( 3.415037499, linear[1][4] )
            self.assertAlmostEqual( 3.299560282, linear[1][5] )
            self.assertAlmostEqual( 3.192645078, linear[1][6] )
            self.assertAlmostEqual( 3.093109404, linear[1][7] )
            self.assertAlmostEqual( 3.         , linear[1][8] )
            self.assertAlmostEqual( 2.850481285, linear[1][9] )
            self.assertAlmostEqual( 2.709511291, linear[1][10] )
            self.assertAlmostEqual( 2.576165116, linear[1][11] )
            self.assertAlmostEqual( 2.449660287, linear[1][12] )
            self.assertAlmostEqual( 2.329328936, linear[1][13] )
            self.assertAlmostEqual( 2.21459646 , linear[1][14] )
            self.assertAlmostEqual( 2.104964924, linear[1][15] )
            self.assertAlmostEqual( 2.         , linear[1][16] )
            self.assertAlmostEqual( 1.858100318, linear[1][17] )
            self.assertAlmostEqual( 1.721766786, linear[1][18] )
            self.assertAlmostEqual( 1.59057916 , linear[1][19] )
            self.assertAlmostEqual( 1.464163065, linear[1][20] )
            self.assertAlmostEqual( 1.34218355 , linear[1][21] )
            self.assertAlmostEqual( 1.224339739, linear[1][22] )
            self.assertAlmostEqual( 1.110360364, linear[1][23] )
            self.assertAlmostEqual( 1.         , linear[1][24] )

        # the data is given explicitly
        chunk = LinearLogTable( x = [ 1., 2., 3., 4. ],
                                y = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = LinearLogTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = LinearLogTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = LinearLogTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = LinearLogTable( x = [ 1., 3., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

        # the x grid has a duplicate point
        with self.assertRaises( Exception ) :

            chunk = LinearLogTable( x = [ 1., 2., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

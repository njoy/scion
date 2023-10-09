# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LogLogTable
from scion.math import IntervalDomain
from scion.math import OpenDomain
from scion.interpolation import InterpolationType

class Test_scion_math_LogLogTable( unittest.TestCase ) :
    """Unit test for the LogLogTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.LogLog, chunk.interpolation )
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
            self.assertAlmostEqual( 3.380457775, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.379516838, chunk( x = 3.5 ) )

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( 1. ) )
            self.assertEqual( True, chunk.is_inside( 2.5 ) )
            self.assertEqual( True, chunk.is_inside( 4. ) )

            self.assertEqual( False, chunk.is_contained( 1. ) )
            self.assertEqual( True, chunk.is_contained( 2.5 ) )
            self.assertEqual( False, chunk.is_contained( 4. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( 1., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 34, len( linear[0] ) )
            self.assertEqual( 34, len( linear[1] ) )

            self.assertAlmostEqual( 1.    , linear[0][0] )
            self.assertAlmostEqual( 1.0625, linear[0][1] )
            self.assertAlmostEqual( 1.125 , linear[0][2] )
            self.assertAlmostEqual( 1.25  , linear[0][3] )
            self.assertAlmostEqual( 1.375 , linear[0][4] )
            self.assertAlmostEqual( 1.5   , linear[0][5] )
            self.assertAlmostEqual( 1.625 , linear[0][6] )
            self.assertAlmostEqual( 1.75  , linear[0][7] )
            self.assertAlmostEqual( 1.875 , linear[0][8] )
            self.assertAlmostEqual( 2.    , linear[0][9] )
            self.assertAlmostEqual( 2.125 , linear[0][10] )
            self.assertAlmostEqual( 2.25  , linear[0][11] )
            self.assertAlmostEqual( 2.375 , linear[0][12] )
            self.assertAlmostEqual( 2.5   , linear[0][13] )
            self.assertAlmostEqual( 2.625 , linear[0][14] )
            self.assertAlmostEqual( 2.75  , linear[0][15] )
            self.assertAlmostEqual( 2.875 , linear[0][16] )
            self.assertAlmostEqual( 3.    , linear[0][17] )
            self.assertAlmostEqual( 3.0625, linear[0][18] )
            self.assertAlmostEqual( 3.125 , linear[0][19] )
            self.assertAlmostEqual( 3.1875, linear[0][20] )
            self.assertAlmostEqual( 3.25  , linear[0][21] )
            self.assertAlmostEqual( 3.3125, linear[0][22] )
            self.assertAlmostEqual( 3.375 , linear[0][23] )
            self.assertAlmostEqual( 3.4375, linear[0][24] )
            self.assertAlmostEqual( 3.5   , linear[0][25] )
            self.assertAlmostEqual( 3.5625, linear[0][26] )
            self.assertAlmostEqual( 3.625 , linear[0][27] )
            self.assertAlmostEqual( 3.6875, linear[0][28] )
            self.assertAlmostEqual( 3.75  , linear[0][29] )
            self.assertAlmostEqual( 3.8125, linear[0][30] )
            self.assertAlmostEqual( 3.875 , linear[0][31] )
            self.assertAlmostEqual( 3.9375, linear[0][32] )
            self.assertAlmostEqual( 4     , linear[0][33] )

            self.assertAlmostEqual( 4.         , linear[1][0] )
            self.assertAlmostEqual( 3.900609682, linear[1][1] )
            self.assertAlmostEqual( 3.809164922, linear[1][2] )
            self.assertAlmostEqual( 3.646185015, linear[1][3] )
            self.assertAlmostEqual( 3.504767277, linear[1][4] )
            self.assertAlmostEqual( 3.380457775, linear[1][5] )
            self.assertAlmostEqual( 3.270001395, linear[1][6] )
            self.assertAlmostEqual( 3.170955062, linear[1][7] )
            self.assertAlmostEqual( 3.08144362 , linear[1][8] )
            self.assertAlmostEqual( 3.         , linear[1][9] )
            self.assertAlmostEqual( 2.823529412, linear[1][10] )
            self.assertAlmostEqual( 2.666666667, linear[1][11] )
            self.assertAlmostEqual( 2.526315789, linear[1][12] )
            self.assertAlmostEqual( 2.4        , linear[1][13] )
            self.assertAlmostEqual( 2.285714286, linear[1][14] )
            self.assertAlmostEqual( 2.181818182, linear[1][15] )
            self.assertAlmostEqual( 2.086956522, linear[1][16] )
            self.assertAlmostEqual( 2.         , linear[1][17] )
            self.assertAlmostEqual( 1.903066705, linear[1][18] )
            self.assertAlmostEqual( 1.812649915, linear[1][19] )
            self.assertAlmostEqual( 1.728194036, linear[1][20] )
            self.assertAlmostEqual( 1.64920048 , linear[1][21] )
            self.assertAlmostEqual( 1.575220866, linear[1][22] )
            self.assertAlmostEqual( 1.50585114 , linear[1][23] )
            self.assertAlmostEqual( 1.440726475, linear[1][24] )
            self.assertAlmostEqual( 1.379516838, linear[1][25] )
            self.assertAlmostEqual( 1.321923126, linear[1][26] )
            self.assertAlmostEqual( 1.267673794, linear[1][27] )
            self.assertAlmostEqual( 1.216521892, linear[1][28] )
            self.assertAlmostEqual( 1.168242471, linear[1][29] )
            self.assertAlmostEqual( 1.122630299, linear[1][30] )
            self.assertAlmostEqual( 1.079497846, linear[1][31] )
            self.assertAlmostEqual( 1.038673501, linear[1][32] )
            self.assertAlmostEqual( 1.         , linear[1][33] )

        # the data is given explicitly
        chunk = LogLogTable( x = [ 1., 2., 3., 4. ],
                             y = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = LogLogTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = LogLogTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = LogLogTable( x = [ 1., 2., 3., 4. ],
                                 y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = LogLogTable( x = [ 1., 3., 2., 4. ],
                                 y = [ 4., 3., 2., 1. ] )

        # the x grid has a duplicate point
        with self.assertRaises( Exception ) :

            chunk = LogLogTable( x = [ 1., 2., 2., 4. ],
                                 y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

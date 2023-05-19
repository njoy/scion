# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LogLogTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_LogLogTable( unittest.TestCase ) :
    """Unit test for the LogLogTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.LogLog, chunk.interpolation )
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
            self.assertAlmostEqual( 3.380457775, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.379516838, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 34, len( linear.x ) )
            self.assertEqual( 34, len( linear.y ) )

            self.assertAlmostEqual( 1.    , linear.x[0] )
            self.assertAlmostEqual( 1.0625, linear.x[1] )
            self.assertAlmostEqual( 1.125 , linear.x[2] )
            self.assertAlmostEqual( 1.25  , linear.x[3] )
            self.assertAlmostEqual( 1.375 , linear.x[4] )
            self.assertAlmostEqual( 1.5   , linear.x[5] )
            self.assertAlmostEqual( 1.625 , linear.x[6] )
            self.assertAlmostEqual( 1.75  , linear.x[7] )
            self.assertAlmostEqual( 1.875 , linear.x[8] )
            self.assertAlmostEqual( 2.    , linear.x[9] )
            self.assertAlmostEqual( 2.125 , linear.x[10] )
            self.assertAlmostEqual( 2.25  , linear.x[11] )
            self.assertAlmostEqual( 2.375 , linear.x[12] )
            self.assertAlmostEqual( 2.5   , linear.x[13] )
            self.assertAlmostEqual( 2.625 , linear.x[14] )
            self.assertAlmostEqual( 2.75  , linear.x[15] )
            self.assertAlmostEqual( 2.875 , linear.x[16] )
            self.assertAlmostEqual( 3.    , linear.x[17] )
            self.assertAlmostEqual( 3.0625, linear.x[18] )
            self.assertAlmostEqual( 3.125 , linear.x[19] )
            self.assertAlmostEqual( 3.1875, linear.x[20] )
            self.assertAlmostEqual( 3.25  , linear.x[21] )
            self.assertAlmostEqual( 3.3125, linear.x[22] )
            self.assertAlmostEqual( 3.375 , linear.x[23] )
            self.assertAlmostEqual( 3.4375, linear.x[24] )
            self.assertAlmostEqual( 3.5   , linear.x[25] )
            self.assertAlmostEqual( 3.5625, linear.x[26] )
            self.assertAlmostEqual( 3.625 , linear.x[27] )
            self.assertAlmostEqual( 3.6875, linear.x[28] )
            self.assertAlmostEqual( 3.75  , linear.x[29] )
            self.assertAlmostEqual( 3.8125, linear.x[30] )
            self.assertAlmostEqual( 3.875 , linear.x[31] )
            self.assertAlmostEqual( 3.9375, linear.x[32] )
            self.assertAlmostEqual( 4     , linear.x[33] )

            self.assertAlmostEqual( 4.         , linear.y[0] )
            self.assertAlmostEqual( 3.900609682, linear.y[1] )
            self.assertAlmostEqual( 3.809164922, linear.y[2] )
            self.assertAlmostEqual( 3.646185015, linear.y[3] )
            self.assertAlmostEqual( 3.504767277, linear.y[4] )
            self.assertAlmostEqual( 3.380457775, linear.y[5] )
            self.assertAlmostEqual( 3.270001395, linear.y[6] )
            self.assertAlmostEqual( 3.170955062, linear.y[7] )
            self.assertAlmostEqual( 3.08144362 , linear.y[8] )
            self.assertAlmostEqual( 3.         , linear.y[9] )
            self.assertAlmostEqual( 2.823529412, linear.y[10] )
            self.assertAlmostEqual( 2.666666667, linear.y[11] )
            self.assertAlmostEqual( 2.526315789, linear.y[12] )
            self.assertAlmostEqual( 2.4        , linear.y[13] )
            self.assertAlmostEqual( 2.285714286, linear.y[14] )
            self.assertAlmostEqual( 2.181818182, linear.y[15] )
            self.assertAlmostEqual( 2.086956522, linear.y[16] )
            self.assertAlmostEqual( 2.         , linear.y[17] )
            self.assertAlmostEqual( 1.903066705, linear.y[18] )
            self.assertAlmostEqual( 1.812649915, linear.y[19] )
            self.assertAlmostEqual( 1.728194036, linear.y[20] )
            self.assertAlmostEqual( 1.64920048 , linear.y[21] )
            self.assertAlmostEqual( 1.575220866, linear.y[22] )
            self.assertAlmostEqual( 1.50585114 , linear.y[23] )
            self.assertAlmostEqual( 1.440726475, linear.y[24] )
            self.assertAlmostEqual( 1.379516838, linear.y[25] )
            self.assertAlmostEqual( 1.321923126, linear.y[26] )
            self.assertAlmostEqual( 1.267673794, linear.y[27] )
            self.assertAlmostEqual( 1.216521892, linear.y[28] )
            self.assertAlmostEqual( 1.168242471, linear.y[29] )
            self.assertAlmostEqual( 1.122630299, linear.y[30] )
            self.assertAlmostEqual( 1.079497846, linear.y[31] )
            self.assertAlmostEqual( 1.038673501, linear.y[32] )
            self.assertAlmostEqual( 1.         , linear.y[33] )

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

if __name__ == '__main__' :

    unittest.main()

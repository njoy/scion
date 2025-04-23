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
            self.assertAlmostEqual( 5., chunk.y[0] )
            self.assertAlmostEqual( 4., chunk.y[1] )
            self.assertAlmostEqual( 3., chunk.y[2] )
            self.assertAlmostEqual( 2., chunk.y[3] )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 5., chunk( x = 1. ) )
            self.assertAlmostEqual( 4., chunk( x = 2. ) )
            self.assertAlmostEqual( 3., chunk( x = 3. ) )
            self.assertAlmostEqual( 2., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 4.388148142366000, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 3.414296578519320, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 2.414154465691340, chunk( x = 3.5 ) )

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

            # verify integration
            self.assertAlmostEqual( 10.3092587344326, chunk.integral )
            self.assertAlmostEqual( 23.545310328628 , chunk.mean )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 24, len( linear[0] ) )
            self.assertEqual( 24, len( linear[1] ) )

            self.assertAlmostEqual( 1.    , linear[0][0] )
            self.assertAlmostEqual( 1.125 , linear[0][1] )
            self.assertAlmostEqual( 1.25  , linear[0][2] )
            self.assertAlmostEqual( 1.375 , linear[0][3] )
            self.assertAlmostEqual( 1.5   , linear[0][4] )
            self.assertAlmostEqual( 1.625 , linear[0][5] )
            self.assertAlmostEqual( 1.75  , linear[0][6] )
            self.assertAlmostEqual( 2.    , linear[0][7] )
            self.assertAlmostEqual( 2.125 , linear[0][8] )
            self.assertAlmostEqual( 2.25  , linear[0][9] )
            self.assertAlmostEqual( 2.375 , linear[0][10] )
            self.assertAlmostEqual( 2.5	  , linear[0][11] )
            self.assertAlmostEqual( 2.625 , linear[0][12] )
            self.assertAlmostEqual( 2.75  , linear[0][13] )
            self.assertAlmostEqual( 2.875 , linear[0][14] )
            self.assertAlmostEqual( 3.    , linear[0][15] )
            self.assertAlmostEqual( 3.125 , linear[0][16] )
            self.assertAlmostEqual( 3.25  , linear[0][17] )
            self.assertAlmostEqual( 3.375 , linear[0][18] )
            self.assertAlmostEqual( 3.5   , linear[0][19] )
            self.assertAlmostEqual( 3.625 , linear[0][20] )
            self.assertAlmostEqual( 3.75  , linear[0][21] )
            self.assertAlmostEqual( 3.875 , linear[0][22] )
            self.assertAlmostEqual( 4.    , linear[0][23] )

            self.assertAlmostEqual( 5.              , linear[1][0] )
            self.assertAlmostEqual( 4.81396102983755, linear[1][1] )
            self.assertAlmostEqual( 4.65341674697485, linear[1][2] )
            self.assertAlmostEqual( 4.51280408869662, linear[1][3] )
            self.assertAlmostEqual( 4.38814814236600, linear[1][4] )
            self.assertAlmostEqual( 4.27651876621215, linear[1][5] )
            self.assertAlmostEqual( 4.17569941137597, linear[1][6] )
            self.assertAlmostEqual( 4.              , linear[1][7] )
            self.assertAlmostEqual( 3.83159247811916, linear[1][8] )
            self.assertAlmostEqual( 3.67931269616815, linear[1][9] )
            self.assertAlmostEqual( 3.54084239458549, linear[1][10] )
            self.assertAlmostEqual( 3.41429657851932, linear[1][11] )
            self.assertAlmostEqual( 3.29812564084982, linear[1][12] )
            self.assertAlmostEqual( 3.19104306545919, linear[1][13] )
            self.assertAlmostEqual( 3.09197119793348, linear[1][14] )
            self.assertAlmostEqual( 3.              , linear[1][15] )
            self.assertAlmostEqual( 2.83226549274327, linear[1][16] )
            self.assertAlmostEqual( 2.67995077927182, linear[1][17] )
            self.assertAlmostEqual( 2.54112379880362, linear[1][18] )
            self.assertAlmostEqual( 2.41415446569134, linear[1][19] )
            self.assertAlmostEqual( 2.29765875214808, linear[1][20] )
            self.assertAlmostEqual( 2.19045463289248, linear[1][21] )
            self.assertAlmostEqual( 2.09152707609899, linear[1][22] )
            self.assertAlmostEqual( 2.              , linear[1][23] )

        # the data is given explicitly
        chunk = LogLogTable( x = [ 1., 2., 3., 4. ],
                             y = [ 5., 4., 3., 2. ] )

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

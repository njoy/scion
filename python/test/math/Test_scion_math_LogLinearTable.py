# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LogLinearTable
from scion.math import IntervalDomain
from scion.math import OpenDomain
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
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 3., chunk( x = 2. ) )
            self.assertAlmostEqual( 2., chunk( x = 3. ) )
            self.assertAlmostEqual( 1., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.464101615, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.414213562, chunk( x = 3.5 ) )

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

            self.assertEqual( 21, len( linear[0] ) )
            self.assertEqual( 21, len( linear[1] ) )

            self.assertAlmostEqual( 1.   , linear[0][0] )
            self.assertAlmostEqual( 1.25 , linear[0][1] )
            self.assertAlmostEqual( 1.5  , linear[0][2] )
            self.assertAlmostEqual( 1.75 , linear[0][3] )
            self.assertAlmostEqual( 2    , linear[0][4] )
            self.assertAlmostEqual( 2.125, linear[0][5] )
            self.assertAlmostEqual( 2.25 , linear[0][6] )
            self.assertAlmostEqual( 2.375, linear[0][7] )
            self.assertAlmostEqual( 2.5  , linear[0][8] )
            self.assertAlmostEqual( 2.625, linear[0][9] )
            self.assertAlmostEqual( 2.75 , linear[0][10] )
            self.assertAlmostEqual( 2.875, linear[0][11] )
            self.assertAlmostEqual( 3.   , linear[0][12] )
            self.assertAlmostEqual( 3.125, linear[0][13] )
            self.assertAlmostEqual( 3.25 , linear[0][14] )
            self.assertAlmostEqual( 3.375, linear[0][15] )
            self.assertAlmostEqual( 3.5  , linear[0][16] )
            self.assertAlmostEqual( 3.625, linear[0][17] )
            self.assertAlmostEqual( 3.75 , linear[0][18] )
            self.assertAlmostEqual( 3.875, linear[0][19] )
            self.assertAlmostEqual( 4.   , linear[0][20] )

            self.assertAlmostEqual( 4.         , linear[1][0] )
            self.assertAlmostEqual( 3.722419436, linear[1][1] )
            self.assertAlmostEqual( 3.464101615, linear[1][2] )
            self.assertAlmostEqual( 3.223709795, linear[1][3] )
            self.assertAlmostEqual( 3          , linear[1][4] )
            self.assertAlmostEqual( 2.851739475, linear[1][5] )
            self.assertAlmostEqual( 2.710806011, linear[1][6] )
            self.assertAlmostEqual( 2.576837503, linear[1][7] )
            self.assertAlmostEqual( 2.449489743, linear[1][8] )
            self.assertAlmostEqual( 2.328435531, linear[1][9] )
            self.assertAlmostEqual( 2.213363839, linear[1][10] )
            self.assertAlmostEqual( 2.103979011, linear[1][11] )
            self.assertAlmostEqual( 2.         , linear[1][12] )
            self.assertAlmostEqual( 1.834008086, linear[1][13] )
            self.assertAlmostEqual( 1.681792831, linear[1][14] )
            self.assertAlmostEqual( 1.542210825, linear[1][15] )
            self.assertAlmostEqual( 1.414213562, linear[1][16] )
            self.assertAlmostEqual( 1.296839555, linear[1][17] )
            self.assertAlmostEqual( 1.189207115, linear[1][18] )
            self.assertAlmostEqual( 1.090507733, linear[1][19] )
            self.assertAlmostEqual( 1.         , linear[1][20] )

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

# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import HistogramTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_HistogramTable( unittest.TestCase ) :
    """Unit test for the HistogramTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.Histogram, chunk.interpolation )
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
            self.assertAlmostEqual( 4., chunk.evaluate( x = 2. ) )
            self.assertAlmostEqual( 3., chunk.evaluate( x = 3. ) )
            self.assertAlmostEqual( 2., chunk.evaluate( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 4., chunk( x = 1.5 ) )
            self.assertAlmostEqual( 3., chunk( x = 2.5 ) )
            self.assertAlmostEqual( 2., chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 6, len( linear.x ) )
            self.assertEqual( 6, len( linear.y ) )

            self.assertAlmostEqual( 1., linear.x[0] )
            self.assertAlmostEqual( 2., linear.x[1] )
            self.assertAlmostEqual( 2., linear.x[2] )
            self.assertAlmostEqual( 3., linear.x[3] )
            self.assertAlmostEqual( 3., linear.x[4] )
            self.assertAlmostEqual( 4., linear.x[5] )

            self.assertAlmostEqual( 4., linear.y[0] )
            self.assertAlmostEqual( 4., linear.y[1] )
            self.assertAlmostEqual( 3., linear.y[2] )
            self.assertAlmostEqual( 3., linear.y[3] )
            self.assertAlmostEqual( 2., linear.y[4] )
            self.assertAlmostEqual( 2., linear.y[5] )

        # the data is given explicitly
        chunk = HistogramTable( x = [ 1., 2., 3., 4. ],
                                y = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = HistogramTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = HistogramTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = HistogramTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = HistogramTable( x = [ 1., 3., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

        # the x grid has a duplicate point
        with self.assertRaises( Exception ) :

            chunk = HistogramTable( x = [ 1., 2., 2., 4. ],
                                    y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LinearLinearTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_LinearLinearTable( unittest.TestCase ) :
    """Unit test for the LinearLinearTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolation )
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
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 1.5, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()
            self.assertEqual( linear.x, chunk.x )
            self.assertEqual( linear.y, chunk.y )

        # the data is given explicitly
        chunk = LinearLinearTable( x = [ 1., 2., 3., 4. ],
                                   y = [ 4., 3., 2., 1. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = LinearLinearTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = LinearLinearTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = LinearLinearTable( x = [ 1., 2., 3., 4. ],
                                       y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = LinearLinearTable( x = [ 1., 3., 2., 4. ],
                                       y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

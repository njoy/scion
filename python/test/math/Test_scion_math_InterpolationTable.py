# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import InterpolationTable
from scion.math import IntervalDomain
from scion.interpolation import InterpolationType

class Test_scion_math_InterpolationTable( unittest.TestCase ) :
    """Unit test for the InterpolationTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk.evaluate( x = 1. ) )
            self.assertAlmostEqual( 3., chunk.evaluate( x = 2. ) )
            self.assertAlmostEqual( 2., chunk.evaluate( x = 3. ) )
            self.assertAlmostEqual( 1., chunk.evaluate( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 2.449660287, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 1.464163065, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 18, len( linear.x ) )
            self.assertEqual( 18, len( linear.y ) )

            self.assertAlmostEqual( 1.   , linear.x[0] )
            self.assertAlmostEqual( 2.   , linear.x[1] )
            self.assertAlmostEqual( 2.125, linear.x[2] )
            self.assertAlmostEqual( 2.25 , linear.x[3] )
            self.assertAlmostEqual( 2.375, linear.x[4] )
            self.assertAlmostEqual( 2.5  , linear.x[5] )
            self.assertAlmostEqual( 2.625, linear.x[6] )
            self.assertAlmostEqual( 2.75 , linear.x[7] )
            self.assertAlmostEqual( 2.875, linear.x[8] )
            self.assertAlmostEqual( 3.   , linear.x[9] )
            self.assertAlmostEqual( 3.125, linear.x[10] )
            self.assertAlmostEqual( 3.25 , linear.x[11] )
            self.assertAlmostEqual( 3.375, linear.x[12] )
            self.assertAlmostEqual( 3.5  , linear.x[13] )
            self.assertAlmostEqual( 3.625, linear.x[14] )
            self.assertAlmostEqual( 3.75 , linear.x[15] )
            self.assertAlmostEqual( 3.875, linear.x[16] )
            self.assertAlmostEqual( 4.   , linear.x[17] )

            self.assertAlmostEqual( 4.         , linear.y[0] )
            self.assertAlmostEqual( 3.         , linear.y[1] )
            self.assertAlmostEqual( 2.850481285, linear.y[2] )
            self.assertAlmostEqual( 2.709511291, linear.y[3] )
            self.assertAlmostEqual( 2.576165116, linear.y[4] )
            self.assertAlmostEqual( 2.449660287, linear.y[5] )
            self.assertAlmostEqual( 2.329328936, linear.y[6] )
            self.assertAlmostEqual( 2.21459646 , linear.y[7] )
            self.assertAlmostEqual( 2.104964924, linear.y[8] )
            self.assertAlmostEqual( 2.         , linear.y[9] )
            self.assertAlmostEqual( 1.858100318, linear.y[10] )
            self.assertAlmostEqual( 1.721766786, linear.y[11] )
            self.assertAlmostEqual( 1.59057916 , linear.y[12] )
            self.assertAlmostEqual( 1.464163065, linear.y[13] )
            self.assertAlmostEqual( 1.34218355 , linear.y[14] )
            self.assertAlmostEqual( 1.224339739, linear.y[15] )
            self.assertAlmostEqual( 1.110360364, linear.y[16] )
            self.assertAlmostEqual( 1.         , linear.y[17] )

        def verify_chunk_jump( self, chunk ) :

            # verify content
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertAlmostEqual( 2., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk.evaluate( x = 1. ) )
            self.assertAlmostEqual( 4., chunk.evaluate( x = 2. ) )
            self.assertAlmostEqual( 3., chunk.evaluate( x = 3. ) )
            self.assertAlmostEqual( 2., chunk.evaluate( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.449660287, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 2.464163065, chunk( x = 3.5 ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 12, len( linear.x ) )
            self.assertEqual( 12, len( linear.y ) )

            self.assertAlmostEqual( 1.   , linear.x[0] )
            self.assertAlmostEqual( 2.   , linear.x[1] )
            self.assertAlmostEqual( 2.   , linear.x[2] )
            self.assertAlmostEqual( 2.125, linear.x[3] )
            self.assertAlmostEqual( 2.25 , linear.x[4] )
            self.assertAlmostEqual( 2.5  , linear.x[5] )
            self.assertAlmostEqual( 2.75 , linear.x[6] )
            self.assertAlmostEqual( 3.   , linear.x[7] )
            self.assertAlmostEqual( 3.25 , linear.x[8] )
            self.assertAlmostEqual( 3.5  , linear.x[9] )
            self.assertAlmostEqual( 3.75 , linear.x[10] )
            self.assertAlmostEqual( 4.   , linear.x[11] )

            self.assertAlmostEqual( 4.         , linear.y[0] )
            self.assertAlmostEqual( 3.         , linear.y[1] )
            self.assertAlmostEqual( 4.         , linear.y[2] )
            self.assertAlmostEqual( 3.850481285, linear.y[3] )
            self.assertAlmostEqual( 3.709511291, linear.y[4] )
            self.assertAlmostEqual( 3.449660287, linear.y[5] )
            self.assertAlmostEqual( 3.21459646 , linear.y[6] )
            self.assertAlmostEqual( 3.         , linear.y[7] )
            self.assertAlmostEqual( 2.721766786, linear.y[8] )
            self.assertAlmostEqual( 2.464163065, linear.y[9] )
            self.assertAlmostEqual( 2.224339739, linear.y[10] )
            self.assertAlmostEqual( 2.         , linear.y[11] )

        # the data is given explicitly for data without a jump
        chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2., 1. ] ,
                                    boundaries = [ 1, 3 ],
                                    interpolants = [ InterpolationType.LinearLinear,
                                                     InterpolationType.LinearLog ] )

        verify_chunk( self, chunk )

        # the data is given explicitly for data with a jump
        chunk = InterpolationTable( x = [ 1., 2., 2., 3., 4. ],
                                    y = [ 4., 3., 4., 3., 2. ] ,
                                    boundaries = [ 1, 4 ],
                                    interpolants = [ InterpolationType.LinearLinear,
                                                     InterpolationType.LinearLog ] )

        verify_chunk_jump( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                       y = [ 4., 3., 2. ] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 3., 2., 4. ],
                                       y = [ 4., 3., 2., 1. ] )

if __name__ == '__main__' :

    unittest.main()

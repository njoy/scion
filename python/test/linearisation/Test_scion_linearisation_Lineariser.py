# standard imports
import unittest

# third party imports
import math

# local imports
from scion.linearisation import Lineariser
from scion.linearisation import MidpointSplit
from scion.linearisation import ToleranceConvergence

class Test_scion_linearisation_Lineariser( unittest.TestCase ) :
    """Unit test for the Lineariser function."""

    def test_Lineariser_minimal_grid( self ) :

        def f( x ) :

            return math.exp( x )

        def split( xLeft, xRight, yLeft, yRight ) :

            return 0.5 * ( xLeft + xRight )

        def convergence( trial, reference, xLeft, xRight, yLeft, yRight ) :

            if ( trial == reference ) : return True
            diff = abs( trial - reference )
            norm = abs( reference )
            return diff < max( norm * 0.25, 1e-10 )

        grid = [ 0., 10. ]

        chunk = Lineariser()

        # the call function accepts python functions
        chunk( grid, f, convergence, split )

        self.assertEqual( 9, len( chunk.x ) )
        self.assertEqual( 9, len( chunk.y ) )

        self.assertAlmostEqual(  0.0 , chunk.x[0] )
        self.assertAlmostEqual(  1.25, chunk.x[1] )
        self.assertAlmostEqual(  2.5 , chunk.x[2] )
        self.assertAlmostEqual(  3.75, chunk.x[3] )
        self.assertAlmostEqual(  5.0 , chunk.x[4] )
        self.assertAlmostEqual(  6.25, chunk.x[5] )
        self.assertAlmostEqual(  7.5 , chunk.x[6] )
        self.assertAlmostEqual(  8.75, chunk.x[7] )
        self.assertAlmostEqual( 10.0 , chunk.x[8] )

        self.assertAlmostEqual( math.exp( 0.0  ), chunk.y[0] )
        self.assertAlmostEqual( math.exp( 1.25 ), chunk.y[1] )
        self.assertAlmostEqual( math.exp( 2.5  ), chunk.y[2] )
        self.assertAlmostEqual( math.exp( 3.75 ), chunk.y[3] )
        self.assertAlmostEqual( math.exp( 5.0  ), chunk.y[4] )
        self.assertAlmostEqual( math.exp( 6.25 ), chunk.y[5] )
        self.assertAlmostEqual( math.exp( 7.5  ), chunk.y[6] )
        self.assertAlmostEqual( math.exp( 8.75 ), chunk.y[7] )
        self.assertAlmostEqual( math.exp(10.0  ), chunk.y[8] )

    def test_Lineariser_minimal_grid( self ) :

        def f( x ) :

            return math.exp( x )

        split = MidpointSplit()
        convergence = ToleranceConvergence( .25 )

        grid = [ 0., 2., 4., 6., 8., 10. ]

        chunk = Lineariser()

        # the call function accepts scion function objects
        chunk( grid, f, convergence, split )

        self.assertEqual( 11, len( chunk.x ) )
        self.assertEqual( 11, len( chunk.y ) )

        self.assertAlmostEqual(  0.0, chunk.x[0] )
        self.assertAlmostEqual(  1.0, chunk.x[1] )
        self.assertAlmostEqual(  2.0, chunk.x[2] )
        self.assertAlmostEqual(  3.0, chunk.x[3] )
        self.assertAlmostEqual(  4.0, chunk.x[4] )
        self.assertAlmostEqual(  5.0, chunk.x[5] )
        self.assertAlmostEqual(  6.0, chunk.x[6] )
        self.assertAlmostEqual(  7.0, chunk.x[7] )
        self.assertAlmostEqual(  8.0, chunk.x[8] )
        self.assertAlmostEqual(  9.0, chunk.x[9] )
        self.assertAlmostEqual( 10.0, chunk.x[10] )

        self.assertAlmostEqual( math.exp(  0.0 ), chunk.y[0] )
        self.assertAlmostEqual( math.exp(  1.0 ), chunk.y[1] )
        self.assertAlmostEqual( math.exp(  2.0 ), chunk.y[2] )
        self.assertAlmostEqual( math.exp(  3.0 ), chunk.y[3] )
        self.assertAlmostEqual( math.exp(  4.0 ), chunk.y[4] )
        self.assertAlmostEqual( math.exp(  5.0 ), chunk.y[5] )
        self.assertAlmostEqual( math.exp(  6.0 ), chunk.y[6] )
        self.assertAlmostEqual( math.exp(  7.0 ), chunk.y[7] )
        self.assertAlmostEqual( math.exp(  8.0 ), chunk.y[8] )
        self.assertAlmostEqual( math.exp(  9.0 ), chunk.y[9] )
        self.assertAlmostEqual( math.exp( 10.0 ), chunk.y[10] )

if __name__ == '__main__' :

    unittest.main()

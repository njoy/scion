# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import LegendreSeries
from scion.math import IntervalDomain

class Test_scion_math_LegendreSeries( unittest.TestCase ) :
    """Unit test for the LegendreSeries class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.order )

            self.assertEqual( 4, len( chunk.coefficients ) )
            self.assertAlmostEqual( 1., chunk.coefficients[0] )
            self.assertAlmostEqual( 2., chunk.coefficients[1] )
            self.assertAlmostEqual( 3., chunk.coefficients[2] )
            self.assertAlmostEqual( 4., chunk.coefficients[3] )

            self.assertEqual( True, isinstance( chunk.domain, IntervalDomain ) )

            self.assertAlmostEqual( -0.5, chunk.evaluate( x =  0. ) )
            self.assertAlmostEqual( 10.0, chunk.evaluate( x =  1. ) )
            self.assertAlmostEqual( -2.0, chunk.evaluate( x = -1. ) )

            self.assertAlmostEqual( -0.5, chunk( x =  0. ) )
            self.assertAlmostEqual( 10.0, chunk( x =  1. ) )
            self.assertAlmostEqual( -2.0, chunk( x = -1. ) )

        # the data is given explicitly
        chunk = LegendreSeries( coefficients = [ 1., 2., 3., 4. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = LegendreSeries( coefficients = [] )

if __name__ == '__main__' :

    unittest.main()

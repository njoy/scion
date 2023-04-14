# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import PolynomialSeries
from scion.math import IntervalDomain

class Test_scion_math_PolynomialSeries( unittest.TestCase ) :
    """Unit test for the PolynomialSeries class."""

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

            self.assertAlmostEqual(  1.0, chunk.evaluate( x =  0. ) )
            self.assertAlmostEqual( 10.0, chunk.evaluate( x =  1. ) )
            self.assertAlmostEqual( -2.0, chunk.evaluate( x = -1. ) )

            self.assertAlmostEqual(  1.0, chunk( x =  0. ) )
            self.assertAlmostEqual( 10.0, chunk( x =  1. ) )
            self.assertAlmostEqual( -2.0, chunk( x = -1. ) )

        # the data is given explicitly
        chunk = PolynomialSeries( lower = -1., upper = 1.,
                                  coefficients = [ 1., 2., 3., 4. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the coefficient vector is empty
        with self.assertRaises( Exception ) :

            chunk = PolynomialSeries( coefficients = [] )

        # the x values are outside the domain
        max = sys.float_info.max
        min = -max
        chunk = PolynomialSeries( lower = -1., upper = 1.,
                                  coefficients = [ 1., 2., 3., 4. ] )
        with self.assertRaises( Exception ) : result = chunk( min )
        with self.assertRaises( Exception ) : result = chunk( -10. )
        with self.assertRaises( Exception ) : result = chunk(  10. )
        with self.assertRaises( Exception ) : result = chunk( max )

if __name__ == '__main__' :

    unittest.main()

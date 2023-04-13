# standard imports
import unittest

# third party imports

# local imports
from scion.math import IntervalDomain

class Test_scion_math_IntervalDomain( unittest.TestCase ) :
    """Unit test for the IntervalDomain class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( -1., chunk.lower_limit )
            self.assertAlmostEqual(  1., chunk.upper_limit )

            # verify functions
            self.assertEqual( True, chunk.is_inside( x = -1.0 ) );
            self.assertEqual( True, chunk.is_inside( x = -0.5 ) );
            self.assertEqual( True, chunk.is_inside( x =  0.0 ) );
            self.assertEqual( True, chunk.is_inside( x =  0.5 ) );
            self.assertEqual( True, chunk.is_inside( x =  1.0 ) );

            self.assertEqual( False, chunk.is_contained( x = -1.0 ) );
            self.assertEqual( True, chunk.is_contained( x = -0.5 ) );
            self.assertEqual( True, chunk.is_contained( x =  0.0 ) );
            self.assertEqual( True, chunk.is_contained( x =  0.5 ) );
            self.assertEqual( False, chunk.is_contained( x =  1.0 ) );

        # the data is given explicitly
        chunk = IntervalDomain( lower = -1., upper = 1. )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # the lower limit is larger than the upper limit
        with self.assertRaises( Exception ) :

            chunk = IntervalDomain( lower = 1., upper = -1. )

        # the lower limit is equal to the upper limit
        with self.assertRaises( Exception ) :

            chunk = IntervalDomain( lower = 1., upper = 1. )

if __name__ == '__main__' :

    unittest.main()

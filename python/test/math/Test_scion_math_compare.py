# standard imports
import unittest

# third party imports

# local imports
from scion.math import is_close, is_close_to_zero

class Test_scion_math_compare( unittest.TestCase ) :
    """Unit test for the comparison functiona."""

    def test_comparison( self ) :

        # floating point comparison
        self.assertEqual( False, is_close( 1., 2. ) )
        self.assertEqual( True, is_close( 1., 1.000000000000015 ) )
        self.assertEqual( True, is_close( 0.999999999999985, 1.000000000000015 ) )

        self.assertEqual( True, is_close( 4.9303807e-32, 4.930381e-32, 1e-4 ) )
        self.assertEqual( True, is_close( 4.9303807e-32, 4.9309825e-32, 1e-4 ) )

        # comparison to zero
        self.assertEqual( True, is_close_to_zero( 0. ) )
        self.assertEqual( False, is_close_to_zero( 1e-10 ) )
        self.assertEqual( False, is_close_to_zero( 1e-12 ) )
        self.assertEqual( True, is_close_to_zero( 1e-20 ) )
        self.assertEqual( True, is_close_to_zero( 1e-22 ) )

if __name__ == '__main__' :

    unittest.main()

# standard imports
import unittest

# third party imports

# local imports
from scion.linearisation import MidpointSplit

class Test_scion_linearisation_MidpointSplit( unittest.TestCase ) :
    """Unit test for the MidpointSplit function."""

    def test_MidpointSplit( self ) :

        yLeft = 1.
        yRight = 2.

        chunk = MidpointSplit();

        self.assertAlmostEqual(  1., chunk( 0., 2., yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()

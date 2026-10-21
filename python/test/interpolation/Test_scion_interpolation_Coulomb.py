# standard imports
import unittest

# third party imports

# local imports
from scion.interpolation import coulomb

class Test_scion_interpolation_coulomb( unittest.TestCase ) :
    """Unit test for the Coulomb penetrability interpolant."""

    def test_interpolation_function( self ) :

        xLeft = 2.0
        xRight = 7.0
        yLeft = 10.0
        yRight = 30.0
        threshold = 0.3

        self.assertAlmostEqual( 10.0, coulomb( 2.0, xLeft, xRight, yLeft, yRight, threshold ) )
        self.assertAlmostEqual( 5.413649473508178, coulomb( 1.5, xLeft, xRight, yLeft, yRight, threshold ) )
        self.assertAlmostEqual( 26.437218001252052, coulomb( 5.0, xLeft, xRight, yLeft, yRight, threshold ) )

if __name__ == '__main__' :

    unittest.main()

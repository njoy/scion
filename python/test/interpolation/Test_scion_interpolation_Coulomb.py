# standard imports
import unittest

# third party imports

# local imports
# from scion.interpolation import InterpolationType
from scion.interpolation import CoulombPenetrability

class Test_scion_interpolation_coulomb( unittest.TestCase ) :
    """Unit test for the lin-lin interpolant."""

    def test_interpolation_function( self ) :

        xLeft = 2.0
        xRight = 7.0
        yLeft = 10.0
        yRight = 30.0
        threshold = 0.3

        integrator = CoulombPenetrability(threshold)

        self.assertAlmostEqual( 10.0, integrator( 2.0, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 5.413649473508178, integrator( 1.5, xLeft, xRight, yLeft, yRight ) )
        self.assertAlmostEqual( 26.437218001252052, integrator( 5.0, xLeft, xRight, yLeft, yRight ) )

if __name__ == '__main__' :

    unittest.main()

# standard imports
import unittest

# third party imports

# local imports
from scion.math import legendre

class Test_scion_math_horner( unittest.TestCase ) :
    """Unit test for the horner function."""

    def test_legendre( self ) :

        self.assertAlmostEqual(  1.0   , legendre( 0, -1.0 ) )
        self.assertAlmostEqual(  1.0   , legendre( 0, -0.5 ) )
        self.assertAlmostEqual(  1.0   , legendre( 0,  0.0 ) )
        self.assertAlmostEqual(  1.0   , legendre( 0,  0.5 ) )
        self.assertAlmostEqual(  1.0   , legendre( 0,  1.0 ) )

        self.assertAlmostEqual( -1.0   , legendre( 1, -1.0 ) )
        self.assertAlmostEqual( -0.5   , legendre( 1, -0.5 ) )
        self.assertAlmostEqual(  0.0   , legendre( 1,  0.0 ) )
        self.assertAlmostEqual(  0.5   , legendre( 1,  0.5 ) )
        self.assertAlmostEqual(  1.0   , legendre( 1,  1.0 ) )

        self.assertAlmostEqual(  1.0   , legendre( 2, -1.0 ) )
        self.assertAlmostEqual( -0.125 , legendre( 2, -0.5 ) )
        self.assertAlmostEqual( -0.5   , legendre( 2,  0.0 ) )
        self.assertAlmostEqual( -0.125 , legendre( 2,  0.5 ) )
        self.assertAlmostEqual(  1.0   , legendre( 2,  1.0 ) )

        self.assertAlmostEqual( -1.0   , legendre( 3, -1.0 ) )
        self.assertAlmostEqual(  0.4375, legendre( 3, -0.5 ) )
        self.assertAlmostEqual(  0.0   , legendre( 3,  0.0 ) )
        self.assertAlmostEqual( -0.4375, legendre( 3,  0.5 ) )
        self.assertAlmostEqual(  1.0   , legendre( 3,  1.0 ) )

if __name__ == '__main__' :

    unittest.main()

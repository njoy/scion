# standard imports
import unittest

# third party imports

# local imports
from scion.math import chebyshev

class Test_scion_math_horner( unittest.TestCase ) :
    """Unit test for the horner function."""

    def test_chebyshev( self ) :

        self.assertAlmostEqual(  1.0, chebyshev( 0, -1.0 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 0, -0.5 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 0,  0.0 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 0,  0.5 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 0,  1.0 ) )

        self.assertAlmostEqual( -1.0, chebyshev( 1, -1.0 ) )
        self.assertAlmostEqual( -0.5, chebyshev( 1, -0.5 ) )
        self.assertAlmostEqual(  0.0, chebyshev( 1,  0.0 ) )
        self.assertAlmostEqual(  0.5, chebyshev( 1,  0.5 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 1,  1.0 ) )

        self.assertAlmostEqual(  1.0, chebyshev( 2, -1.0 ) )
        self.assertAlmostEqual( -0.5, chebyshev( 2, -0.5 ) )
        self.assertAlmostEqual( -1.0, chebyshev( 2,  0.0 ) )
        self.assertAlmostEqual( -0.5, chebyshev( 2,  0.5 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 2,  1.0 ) )

        self.assertAlmostEqual( -1.0, chebyshev( 3, -1.0 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 3, -0.5 ) )
        self.assertAlmostEqual(  0.0, chebyshev( 3,  0.0 ) )
        self.assertAlmostEqual( -1.0, chebyshev( 3,  0.5 ) )
        self.assertAlmostEqual(  1.0, chebyshev( 3,  1.0 ) )

if __name__ == '__main__' :

    unittest.main()

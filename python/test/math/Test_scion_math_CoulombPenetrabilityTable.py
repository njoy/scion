# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import CoulombPenetrabilityTable
from scion.interpolation import InterpolationType

class Test_scion_math_CoulombPenetrabilityTable( unittest.TestCase ) :
    """Unit test for the CoulombPenetrabilityTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( InterpolationType.CoulombPenetrability, chunk.interpolation )
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertAlmostEqual( 2., chunk.x[0] )
            self.assertAlmostEqual( 3., chunk.x[1] )
            self.assertAlmostEqual( 5., chunk.x[2] )
            self.assertAlmostEqual( 7., chunk.x[3] )
            self.assertAlmostEqual( 10., chunk.y[0] )
            self.assertAlmostEqual( 17.735176446201578, chunk.y[1] )
            self.assertAlmostEqual( 26.437218001252052, chunk.y[2] )
            self.assertAlmostEqual( 30., chunk.y[3] )
            self.assertAlmostEqual( 0.3, chunk.threshold )
            self.assertAlmostEqual( 27.658122472732494, chunk( 5.5 ) )
            self.assertAlmostEqual( 24.910475969087816, chunk( 4.5 ) )

            linear = chunk.linearise()
            self.assertAlmostEqual( 12.169490587611747, linear[1][2] )

        # the data is given explicitly
        chunk = CoulombPenetrabilityTable( x = [ 2.0, 3.0, 5.0, 7.0  ],
                                y = [ 10., 17.735176446201578, 26.437218001252052, 30. ],
                                 t = 0.3 )

        verify_chunk( self, chunk)

        # make sure threshold default value is working
        chunk_default = CoulombPenetrabilityTable( x = [ 2.0, 3.0, 5.0, 7.0  ],
                                y = [ 10., 17.735176446201578, 26.437218001252052, 30. ])

        self.assertAlmostEqual( 0.0, chunk_default.threshold )

if __name__ == '__main__' :

    unittest.main()

# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import OpenDomain

class Test_scion_math_OpenDomain( unittest.TestCase ) :
    """Unit test for the OpenDomain class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify functions
            max = sys.float_info.max
            min = -max

            self.assertEqual( True, chunk.is_inside( x = min ) );
            self.assertEqual( True, chunk.is_inside( x = -1.0 ) );
            self.assertEqual( True, chunk.is_inside( x = -0.5 ) );
            self.assertEqual( True, chunk.is_inside( x =  0.0 ) );
            self.assertEqual( True, chunk.is_inside( x =  0.5 ) );
            self.assertEqual( True, chunk.is_inside( x =  1.0 ) );
            self.assertEqual( True, chunk.is_inside( x = max ) );

            self.assertEqual( True, chunk.is_inside( x = min ) );
            self.assertEqual( True, chunk.is_contained( x = -1.0 ) );
            self.assertEqual( True, chunk.is_contained( x = -0.5 ) );
            self.assertEqual( True, chunk.is_contained( x =  0.0 ) );
            self.assertEqual( True, chunk.is_contained( x =  0.5 ) );
            self.assertEqual( True, chunk.is_contained( x =  1.0 ) );
            self.assertEqual( True, chunk.is_inside( x = max ) );

        # the data is given explicitly
        chunk = OpenDomain()

        verify_chunk( self, chunk )

if __name__ == '__main__' :

    unittest.main()

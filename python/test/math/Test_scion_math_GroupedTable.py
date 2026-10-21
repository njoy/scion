# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import GroupedTable

class Test_scion_math_GroupedTable( unittest.TestCase ) :
    """Unit test for the GroupedTable class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 34., chunk.values[0] )
            self.assertAlmostEqual( 35., chunk.values[1] )
            self.assertAlmostEqual( 36., chunk.values[2] )

            # verify arithmetic operators
            result = GroupedTable( [ 0., 32. ], [ 0. ] )
            other = GroupedTable( [ 0., 10., 25., 32. ], [ 1., 2., 3. ] );
            different = GroupedTable( [ 0., 15., 30., 32. ], [ 1., 2., 3. ] );

            chunk += 2.

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 36., chunk.values[0] )
            self.assertAlmostEqual( 37., chunk.values[1] )
            self.assertAlmostEqual( 38., chunk.values[2] )

            chunk -= 2.

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 34., chunk.values[0] )
            self.assertAlmostEqual( 35., chunk.values[1] )
            self.assertAlmostEqual( 36., chunk.values[2] )

            chunk *= 2.

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 68., chunk.values[0] )
            self.assertAlmostEqual( 70., chunk.values[1] )
            self.assertAlmostEqual( 72., chunk.values[2] )

            chunk /= 2.

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 34., chunk.values[0] )
            self.assertAlmostEqual( 35., chunk.values[1] )
            self.assertAlmostEqual( 36., chunk.values[2] )

            result = -chunk

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( -34., result.values[0] )
            self.assertAlmostEqual( -35., result.values[1] )
            self.assertAlmostEqual( -36., result.values[2] )

            result = chunk + 2.

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 36., result.values[0] )
            self.assertAlmostEqual( 37., result.values[1] )
            self.assertAlmostEqual( 38., result.values[2] )

            result = 2. + chunk

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 36., result.values[0] )
            self.assertAlmostEqual( 37., result.values[1] )
            self.assertAlmostEqual( 38., result.values[2] )

            result = chunk - 2.

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 32., result.values[0] )
            self.assertAlmostEqual( 33., result.values[1] )
            self.assertAlmostEqual( 34., result.values[2] )

            result = 2. - chunk

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( -32., result.values[0] )
            self.assertAlmostEqual( -33., result.values[1] )
            self.assertAlmostEqual( -34., result.values[2] )

            result = chunk * 2.

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 68., result.values[0] )
            self.assertAlmostEqual( 70., result.values[1] )
            self.assertAlmostEqual( 72., result.values[2] )

            result = 2. * chunk

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 68., result.values[0] )
            self.assertAlmostEqual( 70., result.values[1] )
            self.assertAlmostEqual( 72., result.values[2] )

            result = chunk / 2

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 17. , result.values[0] )
            self.assertAlmostEqual( 17.5, result.values[1] )
            self.assertAlmostEqual( 18. , result.values[2] )

            chunk += other

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 35., chunk.values[0] )
            self.assertAlmostEqual( 37., chunk.values[1] )
            self.assertAlmostEqual( 39., chunk.values[2] )

            chunk -= other

            self.assertEqual( 3, chunk.number_groups )
            self.assertEqual( 3, len( chunk.values) )
            self.assertEqual( 4, len( chunk.boundaries ) )
            self.assertAlmostEqual(  0., chunk.boundaries[0] )
            self.assertAlmostEqual( 10., chunk.boundaries[1] )
            self.assertAlmostEqual( 25., chunk.boundaries[2] )
            self.assertAlmostEqual( 32., chunk.boundaries[3] )
            self.assertAlmostEqual( 34., chunk.values[0] )
            self.assertAlmostEqual( 35., chunk.values[1] )
            self.assertAlmostEqual( 36., chunk.values[2] )

            result = chunk + other

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 35., result.values[0] )
            self.assertAlmostEqual( 37., result.values[1] )
            self.assertAlmostEqual( 39., result.values[2] )

            result = chunk - other

            self.assertEqual( 3, result.number_groups )
            self.assertEqual( 3, len( result.values) )
            self.assertEqual( 4, len( result.boundaries ) )
            self.assertAlmostEqual(  0., result.boundaries[0] )
            self.assertAlmostEqual( 10., result.boundaries[1] )
            self.assertAlmostEqual( 25., result.boundaries[2] )
            self.assertAlmostEqual( 32., result.boundaries[3] )
            self.assertAlmostEqual( 33., result.values[0] )
            self.assertAlmostEqual( 33., result.values[1] )
            self.assertAlmostEqual( 33., result.values[2] )

            with self.assertRaises( Exception ) : chunk += different
            with self.assertRaises( Exception ) : chunk -= different
            with self.assertRaises( Exception ) : result = chunk + different
            with self.assertRaises( Exception ) : result = chunk - different

        # the data is given explicitly
        chunk = GroupedTable( boundaries = [ 0., 10., 25., 32. ],
                              values = [ 34., 35., 36. ] )

        verify_chunk( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the boundaries or values grid
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [1.0], values = [] )

        # the boundaries and values sizes don't match
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 2., 3. ],
                                  values = [ 4., 3., 2. ] )

        # the boundaries grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 3., 2., 4. ],
                                  values = [ 4., 3., 2. ] )

        # the boundaries grid is not unique
        with self.assertRaises( Exception ) :

            chunk = GroupedTable( boundaries = [ 1., 2., 2., 4. ],
                                  values = [ 4., 3., 2. ] )

if __name__ == '__main__' :

    unittest.main()

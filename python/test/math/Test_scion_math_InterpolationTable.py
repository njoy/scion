# standard imports
import unittest
import sys

# third party imports

# local imports
from scion.math import InterpolationTable
from scion.math import IntervalDomain
from scion.math import OpenDomain
from scion.interpolation import InterpolationType

class Test_scion_math_InterpolationTable( unittest.TestCase ) :
    """Unit test for the InterpolationTable class."""

    def test_component( self ) :

        def verify_chunk1( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 3., chunk( x = 2. ) )
            self.assertAlmostEqual( 2., chunk( x = 3. ) )
            self.assertAlmostEqual( 1., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 2.5, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 1.5, chunk( x = 3.5 ) )

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( 1. ) )
            self.assertEqual( True, chunk.is_inside( 2.5 ) )
            self.assertEqual( True, chunk.is_inside( 4. ) )

            self.assertEqual( False, chunk.is_contained( 1. ) )
            self.assertEqual( True, chunk.is_contained( 2.5 ) )
            self.assertEqual( False, chunk.is_contained( 4. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( 1., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 4, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 4, len( linear.x ) )
            self.assertEqual( 4, len( linear.y ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 3, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1., linear.x[0] )
            self.assertAlmostEqual( 2., linear.x[1] )
            self.assertAlmostEqual( 3., linear.x[2] )
            self.assertAlmostEqual( 4., linear.x[3] )

            self.assertAlmostEqual( 4., linear.y[0] )
            self.assertAlmostEqual( 3., linear.y[1] )
            self.assertAlmostEqual( 2., linear.y[2] )
            self.assertAlmostEqual( 1., linear.y[3] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators
            result = -chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.x[0] )
            self.assertAlmostEqual(  2., result.x[1] )
            self.assertAlmostEqual(  3., result.x[2] )
            self.assertAlmostEqual(  4., result.x[3] )
            self.assertAlmostEqual( -4., result.y[0] )
            self.assertAlmostEqual( -3., result.y[1] )
            self.assertAlmostEqual( -2., result.y[2] )
            self.assertAlmostEqual( -1., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            chunk += 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 6., chunk.y[0] )
            self.assertAlmostEqual( 5., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk -= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk *= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 8., chunk.y[0] )
            self.assertAlmostEqual( 6., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 2., chunk.y[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            chunk /= 2.
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 1, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )

            result = chunk + 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 3., result.x[2] )
            self.assertAlmostEqual( 4., result.x[3] )
            self.assertAlmostEqual( 6., result.y[0] )
            self.assertAlmostEqual( 5., result.y[1] )
            self.assertAlmostEqual( 4., result.y[2] )
            self.assertAlmostEqual( 3., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. + chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 3., result.x[2] )
            self.assertAlmostEqual( 4., result.x[3] )
            self.assertAlmostEqual( 6., result.y[0] )
            self.assertAlmostEqual( 5., result.y[1] )
            self.assertAlmostEqual( 4., result.y[2] )
            self.assertAlmostEqual( 3., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk - 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.x[0] )
            self.assertAlmostEqual(  2., result.x[1] )
            self.assertAlmostEqual(  3., result.x[2] )
            self.assertAlmostEqual(  4., result.x[3] )
            self.assertAlmostEqual(  2., result.y[0] )
            self.assertAlmostEqual(  1., result.y[1] )
            self.assertAlmostEqual(  0., result.y[2] )
            self.assertAlmostEqual( -1., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. - chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.x[0] )
            self.assertAlmostEqual(  2., result.x[1] )
            self.assertAlmostEqual(  3., result.x[2] )
            self.assertAlmostEqual(  4., result.x[3] )
            self.assertAlmostEqual( -2., result.y[0] )
            self.assertAlmostEqual( -1., result.y[1] )
            self.assertAlmostEqual(  0., result.y[2] )
            self.assertAlmostEqual(  1., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk * 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 3., result.x[2] )
            self.assertAlmostEqual( 4., result.x[3] )
            self.assertAlmostEqual( 8., result.y[0] )
            self.assertAlmostEqual( 6., result.y[1] )
            self.assertAlmostEqual( 4., result.y[2] )
            self.assertAlmostEqual( 2., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = 2. * chunk
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 3., result.x[2] )
            self.assertAlmostEqual( 4., result.x[3] )
            self.assertAlmostEqual( 8., result.y[0] )
            self.assertAlmostEqual( 6., result.y[1] )
            self.assertAlmostEqual( 4., result.y[2] )
            self.assertAlmostEqual( 2., result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

            result = chunk / 2.
            self.assertEqual( 4, result.number_points )
            self.assertEqual( 1, result.number_regions )
            self.assertEqual( 4, len( result.x ) )
            self.assertEqual( 4, len( result.y ) )
            self.assertEqual( 1, len( result.boundaries ) )
            self.assertEqual( 1, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.x[0] )
            self.assertAlmostEqual( 2. , result.x[1] )
            self.assertAlmostEqual( 3. , result.x[2] )
            self.assertAlmostEqual( 4. , result.x[3] )
            self.assertAlmostEqual( 2. , result.y[0] )
            self.assertAlmostEqual( 1.5, result.y[1] )
            self.assertAlmostEqual( 1. , result.y[2] )
            self.assertAlmostEqual( 0.5, result.y[3] )
            self.assertEqual( 3, result.boundaries[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )

        def verify_chunk2( self, chunk ) :

            # verify content
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertAlmostEqual( 2., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )
            self.assertEqual( True, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 4., chunk( x = 2. ) )
            self.assertAlmostEqual( 3., chunk( x = 3. ) )
            self.assertAlmostEqual( 2., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )
            self.assertAlmostEqual( 3.5, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 2.5, chunk( x = 3.5 ) )

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( 1. ) )
            self.assertEqual( True, chunk.is_inside( 2.5 ) )
            self.assertEqual( True, chunk.is_inside( 4. ) )

            self.assertEqual( False, chunk.is_contained( 1. ) )
            self.assertEqual( True, chunk.is_contained( 2.5 ) )
            self.assertEqual( False, chunk.is_contained( 4. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( 1., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 5, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 5, len( linear.x ) )
            self.assertEqual( 5, len( linear.y ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual( 1, linear.boundaries[0] )
            self.assertEqual( 4, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1., linear.x[0] )
            self.assertAlmostEqual( 2., linear.x[1] )
            self.assertAlmostEqual( 2., linear.x[2] )
            self.assertAlmostEqual( 3., linear.x[3] )
            self.assertAlmostEqual( 4., linear.x[4] )

            self.assertAlmostEqual( 4., linear.y[0] )
            self.assertAlmostEqual( 3., linear.y[1] )
            self.assertAlmostEqual( 4., linear.y[2] )
            self.assertAlmostEqual( 3., linear.y[3] )
            self.assertAlmostEqual( 2., linear.y[4] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators
            result = -chunk
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.x[0] )
            self.assertAlmostEqual(  2., result.x[1] )
            self.assertAlmostEqual(  2., result.x[2] )
            self.assertAlmostEqual(  3., result.x[3] )
            self.assertAlmostEqual(  4., result.x[4] )
            self.assertAlmostEqual( -4., result.y[0] )
            self.assertAlmostEqual( -3., result.y[1] )
            self.assertAlmostEqual( -4., result.y[2] )
            self.assertAlmostEqual( -3., result.y[3] )
            self.assertAlmostEqual( -2., result.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk += 2.
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 6., chunk.y[0] )
            self.assertAlmostEqual( 5., chunk.y[1] )
            self.assertAlmostEqual( 6., chunk.y[2] )
            self.assertAlmostEqual( 5., chunk.y[3] )
            self.assertAlmostEqual( 4., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk -= 2.
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertAlmostEqual( 2., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk *= 2.
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 8., chunk.y[0] )
            self.assertAlmostEqual( 6., chunk.y[1] )
            self.assertAlmostEqual( 8., chunk.y[2] )
            self.assertAlmostEqual( 6., chunk.y[3] )
            self.assertAlmostEqual( 4., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            chunk /= 2.
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertAlmostEqual( 2., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[1] )

            result = chunk + 2.
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 2., result.x[2] )
            self.assertAlmostEqual( 3., result.x[3] )
            self.assertAlmostEqual( 4., result.x[4] )
            self.assertAlmostEqual( 6., result.y[0] )
            self.assertAlmostEqual( 5., result.y[1] )
            self.assertAlmostEqual( 6., result.y[2] )
            self.assertAlmostEqual( 5., result.y[3] )
            self.assertAlmostEqual( 4., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. + chunk
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 2., result.x[2] )
            self.assertAlmostEqual( 3., result.x[3] )
            self.assertAlmostEqual( 4., result.x[4] )
            self.assertAlmostEqual( 6., result.y[0] )
            self.assertAlmostEqual( 5., result.y[1] )
            self.assertAlmostEqual( 6., result.y[2] )
            self.assertAlmostEqual( 5., result.y[3] )
            self.assertAlmostEqual( 4., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk - 2.
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 2., result.x[2] )
            self.assertAlmostEqual( 3., result.x[3] )
            self.assertAlmostEqual( 4., result.x[4] )
            self.assertAlmostEqual( 2., result.y[0] )
            self.assertAlmostEqual( 1., result.y[1] )
            self.assertAlmostEqual( 2., result.y[2] )
            self.assertAlmostEqual( 1., result.y[3] )
            self.assertAlmostEqual( 0., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. - chunk
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual(  1., result.x[0] )
            self.assertAlmostEqual(  2., result.x[1] )
            self.assertAlmostEqual(  2., result.x[2] )
            self.assertAlmostEqual(  3., result.x[3] )
            self.assertAlmostEqual(  4., result.x[4] )
            self.assertAlmostEqual( -2., result.y[0] )
            self.assertAlmostEqual( -1., result.y[1] )
            self.assertAlmostEqual( -2., result.y[2] )
            self.assertAlmostEqual( -1., result.y[3] )
            self.assertAlmostEqual(  0., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk * 2.
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 2., result.x[2] )
            self.assertAlmostEqual( 3., result.x[3] )
            self.assertAlmostEqual( 4., result.x[4] )
            self.assertAlmostEqual( 8., result.y[0] )
            self.assertAlmostEqual( 6., result.y[1] )
            self.assertAlmostEqual( 8., result.y[2] )
            self.assertAlmostEqual( 6., result.y[3] )
            self.assertAlmostEqual( 4., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = 2. * chunk
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1., result.x[0] )
            self.assertAlmostEqual( 2., result.x[1] )
            self.assertAlmostEqual( 2., result.x[2] )
            self.assertAlmostEqual( 3., result.x[3] )
            self.assertAlmostEqual( 4., result.x[4] )
            self.assertAlmostEqual( 8., result.y[0] )
            self.assertAlmostEqual( 6., result.y[1] )
            self.assertAlmostEqual( 8., result.y[2] )
            self.assertAlmostEqual( 6., result.y[3] )
            self.assertAlmostEqual( 4., result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

            result = chunk / 2.
            self.assertEqual( 5, len( result.x ) )
            self.assertEqual( 5, len( result.y ) )
            self.assertEqual( 2, len( result.boundaries ) )
            self.assertEqual( 2, len( result.interpolants ) )
            self.assertAlmostEqual( 1. , result.x[0] )
            self.assertAlmostEqual( 2. , result.x[1] )
            self.assertAlmostEqual( 2. , result.x[2] )
            self.assertAlmostEqual( 3. , result.x[3] )
            self.assertAlmostEqual( 4. , result.x[4] )
            self.assertAlmostEqual( 2. , result.y[0] )
            self.assertAlmostEqual( 1.5, result.y[1] )
            self.assertAlmostEqual( 2. , result.y[2] )
            self.assertAlmostEqual( 1.5, result.y[3] )
            self.assertAlmostEqual( 1. , result.y[4] )
            self.assertEqual( 1, result.boundaries[0] )
            self.assertEqual( 4, result.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, result.interpolants[1] )

        def verify_chunk3( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.number_points )
            self.assertEqual( 2, chunk.number_regions )
            self.assertEqual( 4, len( chunk.x ) )
            self.assertEqual( 4, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 3., chunk.x[2] )
            self.assertAlmostEqual( 4., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 2., chunk.y[2] )
            self.assertAlmostEqual( 1., chunk.y[3] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 3, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 3., chunk( x = 2. ) )
            self.assertAlmostEqual( 2., chunk( x = 3. ) )
            self.assertAlmostEqual( 1., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 2.44966028678679, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 1.46416306545103, chunk( x = 3.5 ) )

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( 1. ) )
            self.assertEqual( True, chunk.is_inside( 2.5 ) )
            self.assertEqual( True, chunk.is_inside( 4. ) )

            self.assertEqual( False, chunk.is_contained( 1. ) )
            self.assertEqual( True, chunk.is_contained( 2.5 ) )
            self.assertEqual( False, chunk.is_contained( 4. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( 1., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 18, linear.number_points )
            self.assertEqual( 1, linear.number_regions )

            self.assertEqual( 18, len( linear.x ) )
            self.assertEqual( 18, len( linear.y ) )
            self.assertEqual( 1, len( linear.boundaries ) )
            self.assertEqual( 1, len( linear.interpolants ) )

            self.assertEqual( 17, linear.boundaries[0] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )

            self.assertAlmostEqual( 1.   , linear.x[0] )
            self.assertAlmostEqual( 2.   , linear.x[1] )
            self.assertAlmostEqual( 2.125, linear.x[2] )
            self.assertAlmostEqual( 2.25 , linear.x[3] )
            self.assertAlmostEqual( 2.375, linear.x[4] )
            self.assertAlmostEqual( 2.5  , linear.x[5] )
            self.assertAlmostEqual( 2.625, linear.x[6] )
            self.assertAlmostEqual( 2.75 , linear.x[7] )
            self.assertAlmostEqual( 2.875, linear.x[8] )
            self.assertAlmostEqual( 3.   , linear.x[9] )
            self.assertAlmostEqual( 3.125, linear.x[10] )
            self.assertAlmostEqual( 3.25 , linear.x[11] )
            self.assertAlmostEqual( 3.375, linear.x[12] )
            self.assertAlmostEqual( 3.5  , linear.x[13] )
            self.assertAlmostEqual( 3.625, linear.x[14] )
            self.assertAlmostEqual( 3.75 , linear.x[15] )
            self.assertAlmostEqual( 3.875, linear.x[16] )
            self.assertAlmostEqual( 4.   , linear.x[17] )

            self.assertAlmostEqual( 4.              , linear.y[0] )
            self.assertAlmostEqual( 3.              , linear.y[1] )
            self.assertAlmostEqual( 2.85048128530886, linear.y[2] )
            self.assertAlmostEqual( 2.70951129135145, linear.y[3] )
            self.assertAlmostEqual( 2.57616511633150, linear.y[4] )
            self.assertAlmostEqual( 2.44966028678679, linear.y[5] )
            self.assertAlmostEqual( 2.32932893596581, linear.y[6] )
            self.assertAlmostEqual( 2.21459646033567, linear.y[7] )
            self.assertAlmostEqual( 2.10496492439848, linear.y[8] )
            self.assertAlmostEqual( 2.              , linear.y[9] )
            self.assertAlmostEqual( 1.85810031827028, linear.y[10] )
            self.assertAlmostEqual( 1.72176678584324, linear.y[11] )
            self.assertAlmostEqual( 1.59057916034679, linear.y[12] )
            self.assertAlmostEqual( 1.46416306545103, linear.y[13] )
            self.assertAlmostEqual( 1.34218354996644, linear.y[14] )
            self.assertAlmostEqual( 1.22433973930853, linear.y[15] )
            self.assertAlmostEqual( 1.11036036428687, linear.y[16] )
            self.assertAlmostEqual( 1.              , linear.y[17] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators throw exceptions
            temp = InterpolationTable( x = [ 1., 4. ], y = [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = -chunk
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk * 2.
            with self.assertRaises( Exception ) : result = chunk / 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk *= 2.
            with self.assertRaises( Exception ) : chunk /= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk
            with self.assertRaises( Exception ) : result = 2. * chunk

        def verify_chunk4( self, chunk ) :

            # verify content
            self.assertEqual( 5, len( chunk.x ) )
            self.assertEqual( 5, len( chunk.y ) )
            self.assertEqual( 2, len( chunk.boundaries ) )
            self.assertEqual( 2, len( chunk.interpolants ) )
            self.assertAlmostEqual( 1., chunk.x[0] )
            self.assertAlmostEqual( 2., chunk.x[1] )
            self.assertAlmostEqual( 2., chunk.x[2] )
            self.assertAlmostEqual( 3., chunk.x[3] )
            self.assertAlmostEqual( 4., chunk.x[4] )
            self.assertAlmostEqual( 4., chunk.y[0] )
            self.assertAlmostEqual( 3., chunk.y[1] )
            self.assertAlmostEqual( 4., chunk.y[2] )
            self.assertAlmostEqual( 3., chunk.y[3] )
            self.assertAlmostEqual( 2., chunk.y[4] )
            self.assertEqual( 1, chunk.boundaries[0] )
            self.assertEqual( 4, chunk.boundaries[1] )
            self.assertEqual( InterpolationType.LinearLinear, chunk.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLog, chunk.interpolants[1] )
            self.assertEqual( False, chunk.is_linearised )

            # verify evaluation - values of x in the x grid
            self.assertAlmostEqual( 4., chunk( x = 1. ) )
            self.assertAlmostEqual( 4., chunk( x = 2. ) )
            self.assertAlmostEqual( 3., chunk( x = 3. ) )
            self.assertAlmostEqual( 2., chunk( x = 4. ) )

            # verify evaluation - values of x outside the x grid
            self.assertAlmostEqual( 0.0, chunk( x = 0. ) )
            self.assertAlmostEqual( 0.0, chunk( x = 5. ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.5, chunk( x = 1.5 ) )

            # verify evaluation - values of x inside the x grid (lin-lin piece)
            self.assertAlmostEqual( 3.44966028678679, chunk( x = 2.5 ) )
            self.assertAlmostEqual( 2.46416306545103, chunk( x = 3.5 ) )

            # verify domain comparison
            self.assertEqual( True, chunk.is_inside( 1. ) )
            self.assertEqual( True, chunk.is_inside( 2.5 ) )
            self.assertEqual( True, chunk.is_inside( 4. ) )

            self.assertEqual( False, chunk.is_contained( 1. ) )
            self.assertEqual( True, chunk.is_contained( 2.5 ) )
            self.assertEqual( False, chunk.is_contained( 4. ) )

            self.assertEqual( True, chunk.is_same_domain( IntervalDomain( 1., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( IntervalDomain( 0., 4. ) ) )
            self.assertEqual( False, chunk.is_same_domain( OpenDomain() ) )

            # verify linearisation
            linear = chunk.linearise()

            self.assertEqual( 12, linear.number_points )
            self.assertEqual( 2, linear.number_regions )

            self.assertEqual( 12, len( linear.x ) )
            self.assertEqual( 12, len( linear.y ) )
            self.assertEqual( 2, len( linear.boundaries ) )
            self.assertEqual( 2, len( linear.interpolants ) )

            self.assertEqual(  1, linear.boundaries[0] )
            self.assertEqual( 11, linear.boundaries[1] )

            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[0] )
            self.assertEqual( InterpolationType.LinearLinear, linear.interpolants[1] )

            self.assertAlmostEqual( 1.   , linear.x[0] )
            self.assertAlmostEqual( 2.   , linear.x[1] )
            self.assertAlmostEqual( 2.   , linear.x[2] )
            self.assertAlmostEqual( 2.125, linear.x[3] )
            self.assertAlmostEqual( 2.25 , linear.x[4] )
            self.assertAlmostEqual( 2.5  , linear.x[5] )
            self.assertAlmostEqual( 2.75 , linear.x[6] )
            self.assertAlmostEqual( 3.   , linear.x[7] )
            self.assertAlmostEqual( 3.25 , linear.x[8] )
            self.assertAlmostEqual( 3.5  , linear.x[9] )
            self.assertAlmostEqual( 3.75 , linear.x[10] )
            self.assertAlmostEqual( 4.   , linear.x[11] )

            self.assertAlmostEqual( 4.              , linear.y[0] )
            self.assertAlmostEqual( 3.              , linear.y[1] )
            self.assertAlmostEqual( 4.              , linear.y[2] )
            self.assertAlmostEqual( 3.85048128530886, linear.y[3] )
            self.assertAlmostEqual( 3.70951129135145, linear.y[4] )
            self.assertAlmostEqual( 3.44966028678679, linear.y[5] )
            self.assertAlmostEqual( 3.21459646033567, linear.y[6] )
            self.assertAlmostEqual( 3.              , linear.y[7] )
            self.assertAlmostEqual( 2.72176678584324, linear.y[8] )
            self.assertAlmostEqual( 2.46416306545103, linear.y[9] )
            self.assertAlmostEqual( 2.22433973930853, linear.y[10] )
            self.assertAlmostEqual( 2.              , linear.y[11] )

            self.assertEqual( True, linear.is_linearised )

            # verify arithmetic operators throw exceptions
            temp = InterpolationTable( x = [ 1., 4. ], y = [ 4., 1. ] )
            with self.assertRaises( Exception ) : result = -chunk
            with self.assertRaises( Exception ) : result = chunk + 2.
            with self.assertRaises( Exception ) : result = chunk - 2.
            with self.assertRaises( Exception ) : result = chunk * 2.
            with self.assertRaises( Exception ) : result = chunk / 2.
            with self.assertRaises( Exception ) : result = chunk + temp
            with self.assertRaises( Exception ) : result = chunk - temp
            with self.assertRaises( Exception ) : chunk += 2.
            with self.assertRaises( Exception ) : chunk -= 2.
            with self.assertRaises( Exception ) : chunk *= 2.
            with self.assertRaises( Exception ) : chunk /= 2.
            with self.assertRaises( Exception ) : chunk += temp
            with self.assertRaises( Exception ) : chunk -= temp
            with self.assertRaises( Exception ) : result = 2. + chunk
            with self.assertRaises( Exception ) : result = 2. - chunk
            with self.assertRaises( Exception ) : result = 2. * chunk

        # the data is given explicitly for data without boundaries
        chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2., 1. ],
                                    interpolant = InterpolationType.LinearLinear )

        verify_chunk1( self, chunk )

        # the data is given explicitly for data without boundaries and a jump
        chunk = InterpolationTable( x = [ 1., 2., 2., 3., 4. ],
                                    y = [ 4., 3., 4., 3., 2. ],
                                    interpolant = InterpolationType.LinearLinear )

        verify_chunk2( self, chunk )

        # the data is given explicitly for data without a jump
        chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                    y = [ 4., 3., 2., 1. ],
                                    boundaries = [ 1, 3 ],
                                    interpolants = [ InterpolationType.LinearLinear,
                                                     InterpolationType.LinearLog ] )

        verify_chunk3( self, chunk )

        # the data is given explicitly for data with a jump
        chunk = InterpolationTable( x = [ 1., 2., 2., 3., 4. ],
                                    y = [ 4., 3., 4., 3., 2. ],
                                    boundaries = [ 1, 4 ],
                                    interpolants = [ InterpolationType.LinearLinear,
                                                     InterpolationType.LinearLog ] )

        verify_chunk4( self, chunk )

    def test_failures( self ) :

        print( '\n' )

        # there are not enough values in the x or y grid
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [], y = [] )

        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1. ], y = [ 4. ] )

        # the x and y grid do not have the same number of points
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                        y = [ 4., 3., 2. ] )

        # the boundaries and interpolants do not have the same size
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 2., 3., 4. ],
                                        y = [ 4., 3., 2., 1. ],
                                        boundaries = [ 3 ],
                                        interpolants = [] )

        # the x grid is not sorted
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 3., 2., 4. ],
                                        y = [ 4., 3., 2., 1. ] )

        # the x grid contains a triple x value
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 2., 2., 2., 3., 4. ],
                                        y = [ 4., 3., 3., 3., 2., 1. ] )

        # the x grid has a jump at the end
        with self.assertRaises( Exception ) :

            chunk = InterpolationTable( x = [ 1., 2., 4., 4. ],
                                        y = [ 4., 3., 1., 4. ] )

if __name__ == '__main__' :

    unittest.main()

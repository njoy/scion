#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "scion.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding scion Python unit testing" )

add_python_test( interpolation.histogram interpolation/Test_scion_interpolation_histogram.py )
add_python_test( interpolation.linlin interpolation/Test_scion_interpolation_linlin.py )
add_python_test( interpolation.linlog interpolation/Test_scion_interpolation_linlog.py )
add_python_test( interpolation.loglin interpolation/Test_scion_interpolation_loglin.py )
add_python_test( interpolation.loglog interpolation/Test_scion_interpolation_loglog.py )

add_python_test( linearisation.MidpointSplit linearisation/Test_scion_linearisation_MidpointSplit.py )
add_python_test( linearisation.ToleranceConvergence linearisation/Test_scion_linearisation_ToleranceConvergence.py )
add_python_test( linearisation.Lineariser linearisation/Test_scion_linearisation_Lineariser.py )

add_python_test( math.compare math/Test_scion_math_compare.py )
add_python_test( math.newton math/Test_scion_math_newton.py )

add_python_test( math.clenshaw math/Test_scion_math_clenshaw.py )
add_python_test( math.horner math/Test_scion_math_horner.py )

add_python_test( math.chebyshev math/Test_scion_math_chebyshev.py )
add_python_test( math.legendre math/Test_scion_math_legendre.py )

add_python_test( math.IntervalDomain math/Test_scion_math_IntervalDomain.py )
add_python_test( math.OpenDomain math/Test_scion_math_OpenDomain.py )

add_python_test( math.LinearLinearTable math/Test_scion_math_LinearLinearTable.py )
add_python_test( math.HistogramTable math/Test_scion_math_HistogramTable.py )
add_python_test( math.LinearLogTable math/Test_scion_math_LinearLogTable.py )
add_python_test( math.LogLinearTable math/Test_scion_math_LogLinearTable.py )
add_python_test( math.LogLogTable math/Test_scion_math_LogLogTable.py )
add_python_test( math.InterpolationTable math/Test_scion_math_InterpolationTable.py )
add_python_test( math.ChebyshevSeries math/Test_scion_math_ChebyshevSeries.py )
add_python_test( math.ChebyshevApproximation math/Test_scion_math_ChebyshevApproximation.py )
add_python_test( math.LegendreSeries math/Test_scion_math_LegendreSeries.py )
add_python_test( math.PolynomialSeries math/Test_scion_math_PolynomialSeries.py )
